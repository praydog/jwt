#include <vector>
#include <cstdint>
#include <functional>
#include <iostream>

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/buffer.h>
#include <openssl/pem.h>

#include "jwt.hpp"

using namespace std;
using namespace nlohmann;

namespace jwt {
    namespace detail {
        class OnLeave : public vector<function<void()>> {
        public:
            ~OnLeave() {
                for (auto& fn : *this) {
                    fn();
                }
            }
        };

        void replaceAll(string& str, const string& from, const string& to) {
            size_t pos = 0;

            while ((pos = str.find(from, pos)) != string::npos) {
                str.replace(pos, from.length(), to);
                pos += to.length();
            }
        }

        string b64encode(const uint8_t* data, size_t len) {
            auto b64 = BIO_new(BIO_f_base64());
            auto bio = BIO_new(BIO_s_mem());

            bio = BIO_push(b64, bio);

            BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
            BIO_write(bio, data, len);
            BIO_flush(bio);

            BUF_MEM* buf = nullptr;

            BIO_get_mem_ptr(bio, &buf);

            string s{ buf->data };

            BIO_free_all(bio);

            // Convert it to base64url.
            s = s.substr(0, s.find_last_not_of("=") + 1);
            replaceAll(s, "+", "-");
            replaceAll(s, "/", "_");

            return s;
        }

        vector<uint8_t> b64decode(string str) {
            // Convert it from base64url back to normal base64.
            size_t padding{ 0 };

            replaceAll(str, "-", "+");
            replaceAll(str, "_", "/");

            switch (str.length() % 4) {
            case 0:
                break;

            case 2:
                str += "==";
                padding = 2;
                break;

            case 3:
                str += "=";
                padding = 1;
                break;

            default:
                return vector<uint8_t>{};
            }

            size_t len{ (str.length() * 3) / 4 - padding };
            vector<uint8_t> buf(len);

            auto bio = BIO_new_mem_buf((void*)str.c_str(), -1);
            auto b64 = BIO_new(BIO_f_base64());

            bio = BIO_push(b64, bio);

            BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
            BIO_read(bio, buf.data(), str.length());
            BIO_free_all(bio);

            return buf;
        }
    }

    #define SCOPE_EXIT(x) do { onLeave.push_back([&]() { x; }); } while(0)

    string signHMAC(const string& str, const string& key, const string& alg) {
        const EVP_MD* evp = nullptr;

        if (alg == "HS256") {
            evp = EVP_sha256();
        }
        else if (alg == "HS384") {
            evp = EVP_sha384();
        }
        else if (alg == "HS512") {
            evp = EVP_sha512();
        }
        else {
            return string{};
        }

        vector<uint8_t> out(EVP_MAX_MD_SIZE);
        unsigned int len = 0;

        HMAC(evp, key.c_str(), key.length(), (const unsigned char*)str.c_str(), str.length(), out.data(), &len);

        return detail::b64encode(out.data(), len);
    }

    string signPEM(const string& str, const string& key, const string& alg) {
        detail::OnLeave onLeave{};
        const EVP_MD* evp = nullptr;

        if (alg == "RS256") {
            evp = EVP_sha256();
        }
        else if (alg == "RS384") {
            evp = EVP_sha384();
        }
        else if (alg == "RS512") {
            evp = EVP_sha512();
        }
        else if (alg == "ES256") {
            evp = EVP_sha256();
        }
        else if (alg == "ES384") {
            evp = EVP_sha384();
        }
        else if (alg == "ES512") {
            evp = EVP_sha512();
        }
        else {
            return string{};
        }

        auto bufkey = BIO_new_mem_buf((void*)key.c_str(), key.length());
        SCOPE_EXIT(if (bufkey) BIO_free(bufkey));

        if (!bufkey) {
            return string{};
        }

        // Use OpenSSL's default passphrase callbacks if needed.
        auto pkey = PEM_read_bio_PrivateKey(bufkey, nullptr, nullptr, nullptr);
        SCOPE_EXIT(if (pkey) EVP_PKEY_free(pkey));

        if (!pkey) {
            return string{};
        }

        auto mdctx = EVP_MD_CTX_create();
        SCOPE_EXIT(if (mdctx) EVP_MD_CTX_destroy(mdctx));

        if (!mdctx) {
            return string{};
        }

        // Initialize the digest sign operation.
        if (EVP_DigestSignInit(mdctx, nullptr, evp, nullptr, pkey) != 1) {
            return string{};
        }

        // Update the digest sign with the message.
        if (EVP_DigestSignUpdate(mdctx, str.c_str(), str.length()) != 1) {
            return string{};
        }

        // Determin the size of the finalized digest sign.
        size_t siglen = 0;

        if (EVP_DigestSignFinal(mdctx, nullptr, &siglen) != 1) {
            return string{};
        }

        // Finalize it.
        vector<uint8_t> sig(siglen);

        if (EVP_DigestSignFinal(mdctx, sig.data(), &siglen) != 1) {
            return string{};
        }

        // For RSA, we are done.
        return detail::b64encode(sig.data(), siglen);
    }

    bool verifyPEM(const string& str, const string& b64sig, const string& key, const string& alg) {
        detail::OnLeave onLeave{};
        const EVP_MD* evp = nullptr;

        if (alg == "RS256") {
            evp = EVP_sha256();
        }
        else if (alg == "RS384") {
            evp = EVP_sha384();
        }
        else if (alg == "RS512") {
            evp = EVP_sha512();
        }
        else if (alg == "ES256") {
            evp = EVP_sha256();
        }
        else if (alg == "ES384") {
            evp = EVP_sha384();
        }
        else if (alg == "ES512") {
            evp = EVP_sha512();
        }
        else {
            return false;
        }

        auto sig = detail::b64decode(b64sig);
        auto siglen = sig.size();

        if (sig.empty()) {
            return false;
        }

        auto bufkey = BIO_new_mem_buf((void*)key.c_str(), key.length());
        SCOPE_EXIT(if (bufkey) BIO_free(bufkey));

        if (!bufkey) {
            return false;
        }

        // Use OpenSSL's default passphrase callbacks if needed.
        auto pkey = PEM_read_bio_PUBKEY(bufkey, nullptr, nullptr, nullptr);
        SCOPE_EXIT(if (pkey) EVP_PKEY_free(pkey));

        if (!pkey) {
            return false;
        }

        auto mdctx = EVP_MD_CTX_create();
        SCOPE_EXIT(if (mdctx) EVP_MD_CTX_destroy(mdctx));

        if (EVP_DigestVerifyInit(mdctx, nullptr, evp, nullptr, pkey) != 1) {
            return false;
        }

        if (EVP_DigestVerifyUpdate(mdctx, str.c_str(), str.length()) != 1) {
            return false;
        }

        if (EVP_DigestVerifyFinal(mdctx, sig.data(), siglen) != 1) {
            return false;
        }

        return true;
    }

    string encode(const json& payload, const string& key, const string& alg) {
        // Create a JWT header defaulting to the HS256 alg if none is supplied.
        json header{
            {"typ", "JWT"},
            {"alg", alg.empty() ? "HS256" : alg }
        };
        auto headerStr = header.dump();
        auto encodedHeader = detail::b64encode((const uint8_t*)headerStr.c_str(), headerStr.length());

        // Encode the payload.
        auto payloadStr = payload.dump();
        auto encodedPayload = detail::b64encode((const uint8_t*)payloadStr.c_str(), payloadStr.length());

        // Sign it and return the final JWT.
        auto encodedToken = encodedHeader + "." + encodedPayload;
        const string& theAlg = header["alg"];
        string signature{};

        if (theAlg == "none") {
            // Nothing to sign.
        }
        else if (theAlg.find("HS") != string::npos) {
            signature = signHMAC(encodedToken, key, theAlg);
        }
        else {
            signature = signPEM(encodedToken, key, theAlg);
        }

        if (theAlg != "none" && signature.empty()) {
            return string{};
        }

        return encodedToken + "." + signature;
    }

    json decode(const string& jwt, const string& key, const set<string>& alg) {
        if (jwt.empty()) {
            return json{};
        }

        // Make sure the jwt we recieve looks like a jwt.
        auto firstPeriod = jwt.find_first_of('.');
        auto secondPeriod = jwt.find_first_of('.', firstPeriod + 1);

        if (firstPeriod == string::npos || secondPeriod == string::npos) {
            return json{};
        }

        // Decode the header so we can get the alg used by the jwt.
        auto decodedHeader = detail::b64decode(jwt.substr(0, firstPeriod));
        string decodedHeaderStr{ decodedHeader.begin(), decodedHeader.end() };
        auto header = json::parse(decodedHeaderStr.c_str());
        const string& theAlg = header["alg"];

        // Make sure no key is supplied if the alg is none.
        if (theAlg == "none" && !key.empty()) {
            return json{};
        }
        // Make sure the alg supplied is one we expect.
        else if (alg.count(theAlg) == 0 && !alg.empty()) {
            return json{};
        }

        auto encodedToken = jwt.substr(0, secondPeriod);
        auto signature = jwt.substr(secondPeriod + 1);

        // Verify the signature.
        if (theAlg == "none") {
            // Nothing to do, no verification needed.
        }
        else if (theAlg.find("HS") != string::npos) {
            auto calculatedSignature = signHMAC(encodedToken, key, theAlg);

            if (signature != calculatedSignature || calculatedSignature.empty()) {
                return json{};
            }
        }
        else {
            if (!verifyPEM(encodedToken, signature, key, theAlg)) {
                return json{};
            }
        }

        // Decode the payload since the jwt has been verified.
        auto decodedPayload = detail::b64decode(jwt.substr(firstPeriod + 1, secondPeriod - firstPeriod - 1));
        string decodedPayloadStr{ decodedPayload.begin(), decodedPayload.end() };
        auto payload = json::parse(decodedPayloadStr.c_str());

        return payload;
    }
}