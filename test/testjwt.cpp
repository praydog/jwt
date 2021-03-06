#include <string>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "jwt/jwt.hpp"
#include "jwt/json.hpp"

using namespace std;
using namespace nlohmann;

SCENARIO("Invalid signatures cause decoding to fail") {
    string hsKey{ "secret" };
    auto rsPublicKey = R"(
-----BEGIN PUBLIC KEY-----
MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQC8kGa1pSjbSYZVebtTRBLxBz5H
4i2p/llLCrEeQhta5kaQu/RnvuER4W8oDH3+3iuIYW4VQAzyqFpwuzjkDI+17t5t
0tyazyZ8JXw+KgXTxldMPEL95+qVhgXvwtihXC1c5oGbRlEDvDF6Sa53rcFVsYJ4
ehde/zUxo6UvS7UrBQIDAQAB
-----END PUBLIC KEY-----
)";
    auto esPublicKey = R"(
-----BEGIN PUBLIC KEY-----
MIGbMBAGByqGSM49AgEGBSuBBAAjA4GGAAQAR/acP0tFaeapRIWFpPsApcRYiFc5
OvmzlRcJrINzShRBHZKufJ6/A2+XNquYETqpnHYwXFKlo/Ne0Zs8pKfz0EwAP6/z
hdCHLPADaPT8ghKSn4knIKTcUrj8apbtkiEZ+7wtltyHEah825dTCSeLspOLfDTN
4S1lJWUVZN1moK4h0aI=
-----END PUBLIC KEY-----
)";

    GIVEN("An HS256 encoded token with an invalid signature") {
        string encodedToken{ "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiYWRtaW4iOnRydWV9" };
        auto encoded = encodedToken + ".aW52YWxpZA";

        WHEN("it is decoded") {
            auto decoded = jwt::decode(encoded, hsKey);
            
            THEN("it returns null") {
                REQUIRE(decoded == nullptr);
            }
        }
    }

    GIVEN("An HS384 encoded token with an invalid signature") {
        string encodedToken{ "eyJhbGciOiJIUzM4NCIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiYWRtaW4iOnRydWV9" };
        auto encoded = encodedToken + ".aW52YWxpZA";

        WHEN("it is decoded") {
            auto decoded = jwt::decode(encoded, hsKey);
            
            THEN("it returns null") {
                REQUIRE(decoded == nullptr);
            }
        }
    }

    GIVEN("An HS512 encoded token with an invalid signature") {
        string encodedToken{ "eyJhbGciOiJIUzUxMiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiYWRtaW4iOnRydWV9" };
        auto encoded = encodedToken + ".aW52YWxpZA";

        WHEN("it is decoded") {
            auto decoded = jwt::decode(encoded, hsKey);
            
            THEN("it returns null") {
                REQUIRE(decoded == nullptr);
            }
        }
    }

    GIVEN("An RS256 encoded token with an invalid signature") {
        string encodedToken{ "eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiYWRtaW4iOnRydWV9" };
        auto encoded = encodedToken + ".aW52YWxpZA";

        WHEN("it is decoded") {
            auto decoded = jwt::decode(encoded, rsPublicKey);
            
            THEN("it returns null") {
                REQUIRE(decoded == nullptr);
            }
        }
    }

    GIVEN("An RS384 encoded token with an invalid signature") {
        string encodedToken{ "eyJhbGciOiJSUzM4NCIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiYWRtaW4iOnRydWV9" };
        auto encoded = encodedToken + ".aW52YWxpZA";

        WHEN("it is decoded") {
            auto decoded = jwt::decode(encoded, rsPublicKey);

            THEN("it returns null") {
                REQUIRE(decoded == nullptr);
            }
        }
    }

    GIVEN("An RS512 encoded token with an invalid signature") {
        string encodedToken{ "eyJhbGciOiJSUzUxMiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiYWRtaW4iOnRydWV9" };
        auto encoded = encodedToken + ".aW52YWxpZA";

        WHEN("it is decoded") {
            auto decoded = jwt::decode(encoded, rsPublicKey);

            THEN("it returns null") {
                REQUIRE(decoded == nullptr);
            }
        }
    }


    GIVEN("An ES256 encoded token with an invalid signature") {
        string encodedToken{ "eyJhbGciOiJFUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiYWRtaW4iOnRydWV9" };
        auto encoded = encodedToken + ".aW52YWxpZA";

        WHEN("it is decoded") {
            auto decoded = jwt::decode(encoded, esPublicKey);
            
            THEN("it returns null") {
                REQUIRE(decoded == nullptr);
            }
        }
    }

    GIVEN("An ES384 encoded token with an invalid signature") {
        string encodedToken{ "eyJhbGciOiJFUzM4NCIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiYWRtaW4iOnRydWV9" };
        auto encoded = encodedToken + ".aW52YWxpZA";

        WHEN("it is decoded") {
            auto decoded = jwt::decode(encoded, esPublicKey);

            THEN("it returns null") {
                REQUIRE(decoded == nullptr);
            }
        }
    }

    GIVEN("An ES512 encoded token with an invalid signature") {
        string encodedToken{ "eyJhbGciOiJFUzUxMiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiYWRtaW4iOnRydWV9" };
        auto encoded = encodedToken + ".aW52YWxpZA";

        WHEN("it is decoded") {
            auto decoded = jwt::decode(encoded, esPublicKey);

            THEN("it returns null") {
                REQUIRE(decoded == nullptr);
            }
        }
    }
}

SCENARIO("Invalid parameters cause decoding to fail") {
    string key{ "secret" };
    auto payload = R"(
        {
            "sub": "1234567890",
            "name": "John Doe",
            "admin": true
        }
    )"_json;

    GIVEN("some payload") {
        WHEN("encoded with an invalid algorithm") {
            auto encoded = jwt::encode(payload, key, { "HK256" });

            THEN("it returns an empty string") {
                REQUIRE(encoded.empty());
            }
        }
    }

    GIVEN("An empty string") {
        string encoded{};

        WHEN("it is decoded") {
            auto decoded = jwt::decode(encoded, key);

            THEN("it fails to decode by returning nullptr") {
                REQUIRE(decoded == nullptr);
            }
        }
    }
}

SCENARIO("JWT's can be encoded and decoded using no alg") {
    auto payload = R"(
        {
            "sub": "1234567890",
            "name": "John Doe",
            "admin": true
        }
    )"_json;

    GIVEN("An encoded payload") {
        auto encoded = jwt::encode(payload, "", "none");

        WHEN("it is decoded") {
            auto decoded = jwt::decode(encoded, "", { "none" });

            THEN("it equals the payload") {
                REQUIRE(decoded == payload);
            }
        }

        WHEN("it is auto decoded with no algorithms specified") {
            auto decoded = jwt::decode(encoded, "");

            THEN("the algorithm is determined by the token and properly decoded") {
                REQUIRE(decoded == payload);
            }
        }

        WHEN("it is decoded with the wrong algorithms specified") {
            auto decoded = jwt::decode(encoded, "", { "HS384" });

            THEN("it returns null") {
                REQUIRE(decoded == nullptr);
            }
        }

        WHEN("it is decoded with a key") {
            auto decoded = jwt::decode(encoded, "secret");

            THEN("it returns null") {
                REQUIRE(decoded == nullptr);
            }
        }

        WHEN("it is decoded with a key and 'none' specified") {
            auto decoded = jwt::decode(encoded, "secret", { "none" });

            THEN("it returns null") {
                REQUIRE(decoded == nullptr);
            }
        }
    }
}

SCENARIO("JWT's can be encoded and decoded using HS256") {
    string key{ "secret" };
    auto payload = R"(
        {
            "sub": "1234567890",
            "name": "John Doe",
            "admin": true
        }
    )"_json;

    GIVEN("An encoded payload") {
        auto encoded = jwt::encode(payload, key, "HS256");

        WHEN("it is decoded") {
            auto decoded = jwt::decode(encoded, key, { "HS256" });
             
            THEN("it equals the payload") {
                REQUIRE(decoded == payload);
            }
        }

        WHEN("it is auto decoded with no algorithms specified") {
            auto decoded = jwt::decode(encoded, key);

            THEN("the algorithm is determined by the token and properly decoded") {
                REQUIRE(decoded == payload);
            }
        }

        WHEN("it is decoded with the wrong algorithms specified") {
            auto decoded = jwt::decode(encoded, key, { "HS384" });

            THEN("it returns null") {
                REQUIRE(decoded == nullptr);
            }
        }
    }
}

SCENARIO("JWT's can be encoded and decoded using HS384") {
    string key{ "secret" };
    auto payload = R"(
        {
            "sub": "1234567890",
            "name": "John Doe",
            "admin": true
        }
    )"_json;

    GIVEN("An encoded payload") {
        auto encoded = jwt::encode(payload, key, "HS384");

        WHEN("it is decoded") {
            auto decoded = jwt::decode(encoded, key, { "HS384" });
             
            THEN("it equals the payload") {
                REQUIRE(decoded == payload);
            }
        }

        WHEN("it is auto decoded with no algorithms specified") {
            auto decoded = jwt::decode(encoded, key);

            THEN("the algorithm is determined by the token and properly decoded") {
                REQUIRE(decoded == payload);
            }
        }

        WHEN("it is decoded with the wrong algorithms specified") {
            auto decoded = jwt::decode(encoded, key, { "HS512" });

            THEN("it returns null") {
                REQUIRE(decoded == nullptr);
            }
        }
    }
}

SCENARIO("JWT's can be encoded and decoded using HS512") {
    string key{ "secret" };
    auto payload = R"(
        {
            "sub": "1234567890",
            "name": "John Doe",
            "admin": true
        }
    )"_json;

    GIVEN("An encoded payload") {
        auto encoded = jwt::encode(payload, key, "HS512");

        WHEN("it is decoded") {
            auto decoded = jwt::decode(encoded, key, { "HS512" });
             
            THEN("it equals the payload") {
                REQUIRE(decoded == payload);
            }
        }

        WHEN("it is auto decoded with no algorithms specified") {
            auto decoded = jwt::decode(encoded, key);

            THEN("the algorithm is determined by the token and properly decoded") {
                REQUIRE(decoded == payload);
            }
        }

        WHEN("it is decoded with the wrong algorithms specified") {
            auto decoded = jwt::decode(encoded, key, { "HS256" });

            THEN("it returns null") {
                REQUIRE(decoded == nullptr);
            }
        }
    }
}

SCENARIO("JWT's can be encoded and decoded using RS256") {
    auto payload = R"(
        {
            "sub": "1234567890",
            "name": "John Doe",
            "admin": true
        }
    )"_json;
    auto privateKey = R"(
-----BEGIN RSA PRIVATE KEY-----
MIICXAIBAAKBgQC8kGa1pSjbSYZVebtTRBLxBz5H4i2p/llLCrEeQhta5kaQu/Rn
vuER4W8oDH3+3iuIYW4VQAzyqFpwuzjkDI+17t5t0tyazyZ8JXw+KgXTxldMPEL9
5+qVhgXvwtihXC1c5oGbRlEDvDF6Sa53rcFVsYJ4ehde/zUxo6UvS7UrBQIDAQAB
AoGAb/MXV46XxCFRxNuB8LyAtmLDgi/xRnTAlMHjSACddwkyKem8//8eZtw9fzxz
bWZ/1/doQOuHBGYZU8aDzzj59FZ78dyzNFoF91hbvZKkg+6wGyd/LrGVEB+Xre0J
Nil0GReM2AHDNZUYRv+HYJPIOrB0CRczLQsgFJ8K6aAD6F0CQQDzbpjYdx10qgK1
cP59UHiHjPZYC0loEsk7s+hUmT3QHerAQJMZWC11Qrn2N+ybwwNblDKv+s5qgMQ5
5tNoQ9IfAkEAxkyffU6ythpg/H0Ixe1I2rd0GbF05biIzO/i77Det3n4YsJVlDck
ZkcvY3SK2iRIL4c9yY6hlIhs+K9wXTtGWwJBAO9Dskl48mO7woPR9uD22jDpNSwe
k90OMepTjzSvlhjbfuPN1IdhqvSJTDychRwn1kIJ7LQZgQ8fVz9OCFZ/6qMCQGOb
qaGwHmUK6xzpUbbacnYrIM6nLSkXgOAwv7XXCojvY614ILTK3iXiLBOxPu5Eu13k
eUz9sHyD6vkgZzjtxXECQAkp4Xerf5TGfQXGXhxIX52yH+N2LtujCdkQZjXAsGdm
B2zNzvrlgRmgBrklMTrMYgm1NPcW+bRLGcwgW2PTvNM=
-----END RSA PRIVATE KEY-----
)";
    auto publicKey = R"(
-----BEGIN PUBLIC KEY-----
MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQC8kGa1pSjbSYZVebtTRBLxBz5H
4i2p/llLCrEeQhta5kaQu/RnvuER4W8oDH3+3iuIYW4VQAzyqFpwuzjkDI+17t5t
0tyazyZ8JXw+KgXTxldMPEL95+qVhgXvwtihXC1c5oGbRlEDvDF6Sa53rcFVsYJ4
ehde/zUxo6UvS7UrBQIDAQAB
-----END PUBLIC KEY-----
)";

    GIVEN("An encoded payload using a private key") {
        auto encoded = jwt::encode(payload, privateKey, "RS256");

        WHEN("it is decoded using a public key") {
            auto decoded = jwt::decode(encoded, publicKey, { "RS256" });
             
            THEN("it equals the payload") {
                REQUIRE(decoded == payload);
            }
        }

        WHEN("it is auto decoded with no algorithms specified") {
            auto decoded = jwt::decode(encoded, publicKey);

            THEN("the algorithm is determined by the token and properly decoded") {
                REQUIRE(decoded == payload);
            }
        }

        WHEN("it is decoded with the wrong algorithms specified") {
            auto decoded = jwt::decode(encoded, publicKey, { "RS384" });

            THEN("it returns null") {
                REQUIRE(decoded == nullptr);
            }
        }
    }
}

SCENARIO("JWT's can be encoded and decoded using RS384") {
    auto payload = R"(
        {
            "sub": "1234567890",
            "name": "John Doe",
            "admin": true
        }
    )"_json;
    auto privateKey = R"(
-----BEGIN RSA PRIVATE KEY-----
MIICXAIBAAKBgQC8kGa1pSjbSYZVebtTRBLxBz5H4i2p/llLCrEeQhta5kaQu/Rn
vuER4W8oDH3+3iuIYW4VQAzyqFpwuzjkDI+17t5t0tyazyZ8JXw+KgXTxldMPEL9
5+qVhgXvwtihXC1c5oGbRlEDvDF6Sa53rcFVsYJ4ehde/zUxo6UvS7UrBQIDAQAB
AoGAb/MXV46XxCFRxNuB8LyAtmLDgi/xRnTAlMHjSACddwkyKem8//8eZtw9fzxz
bWZ/1/doQOuHBGYZU8aDzzj59FZ78dyzNFoF91hbvZKkg+6wGyd/LrGVEB+Xre0J
Nil0GReM2AHDNZUYRv+HYJPIOrB0CRczLQsgFJ8K6aAD6F0CQQDzbpjYdx10qgK1
cP59UHiHjPZYC0loEsk7s+hUmT3QHerAQJMZWC11Qrn2N+ybwwNblDKv+s5qgMQ5
5tNoQ9IfAkEAxkyffU6ythpg/H0Ixe1I2rd0GbF05biIzO/i77Det3n4YsJVlDck
ZkcvY3SK2iRIL4c9yY6hlIhs+K9wXTtGWwJBAO9Dskl48mO7woPR9uD22jDpNSwe
k90OMepTjzSvlhjbfuPN1IdhqvSJTDychRwn1kIJ7LQZgQ8fVz9OCFZ/6qMCQGOb
qaGwHmUK6xzpUbbacnYrIM6nLSkXgOAwv7XXCojvY614ILTK3iXiLBOxPu5Eu13k
eUz9sHyD6vkgZzjtxXECQAkp4Xerf5TGfQXGXhxIX52yH+N2LtujCdkQZjXAsGdm
B2zNzvrlgRmgBrklMTrMYgm1NPcW+bRLGcwgW2PTvNM=
-----END RSA PRIVATE KEY-----
)";
    auto publicKey = R"(
-----BEGIN PUBLIC KEY-----
MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQC8kGa1pSjbSYZVebtTRBLxBz5H
4i2p/llLCrEeQhta5kaQu/RnvuER4W8oDH3+3iuIYW4VQAzyqFpwuzjkDI+17t5t
0tyazyZ8JXw+KgXTxldMPEL95+qVhgXvwtihXC1c5oGbRlEDvDF6Sa53rcFVsYJ4
ehde/zUxo6UvS7UrBQIDAQAB
-----END PUBLIC KEY-----
)";

    GIVEN("An encoded payload using a private key") {
        auto encoded = jwt::encode(payload, privateKey, "RS384");

        WHEN("it is decoded using a public key") {
            auto decoded = jwt::decode(encoded, publicKey, { "RS384" });

            THEN("it equals the payload") {
                REQUIRE(decoded == payload);
            }
        }

        WHEN("it is auto decoded with no algorithms specified") {
            auto decoded = jwt::decode(encoded, publicKey);

            THEN("the algorithm is determined by the token and properly decoded") {
                REQUIRE(decoded == payload);
            }
        }

        WHEN("it is decoded with the wrong algorithms specified") {
            auto decoded = jwt::decode(encoded, publicKey, { "RS512" });

            THEN("it returns null") {
                REQUIRE(decoded == nullptr);
            }
        }
    }
}

SCENARIO("JWT's can be encoded and decoded using RS512") {
    auto payload = R"(
        {
            "sub": "1234567890",
            "name": "John Doe",
            "admin": true
        }
    )"_json;
    auto privateKey = R"(
-----BEGIN RSA PRIVATE KEY-----
MIICXAIBAAKBgQC8kGa1pSjbSYZVebtTRBLxBz5H4i2p/llLCrEeQhta5kaQu/Rn
vuER4W8oDH3+3iuIYW4VQAzyqFpwuzjkDI+17t5t0tyazyZ8JXw+KgXTxldMPEL9
5+qVhgXvwtihXC1c5oGbRlEDvDF6Sa53rcFVsYJ4ehde/zUxo6UvS7UrBQIDAQAB
AoGAb/MXV46XxCFRxNuB8LyAtmLDgi/xRnTAlMHjSACddwkyKem8//8eZtw9fzxz
bWZ/1/doQOuHBGYZU8aDzzj59FZ78dyzNFoF91hbvZKkg+6wGyd/LrGVEB+Xre0J
Nil0GReM2AHDNZUYRv+HYJPIOrB0CRczLQsgFJ8K6aAD6F0CQQDzbpjYdx10qgK1
cP59UHiHjPZYC0loEsk7s+hUmT3QHerAQJMZWC11Qrn2N+ybwwNblDKv+s5qgMQ5
5tNoQ9IfAkEAxkyffU6ythpg/H0Ixe1I2rd0GbF05biIzO/i77Det3n4YsJVlDck
ZkcvY3SK2iRIL4c9yY6hlIhs+K9wXTtGWwJBAO9Dskl48mO7woPR9uD22jDpNSwe
k90OMepTjzSvlhjbfuPN1IdhqvSJTDychRwn1kIJ7LQZgQ8fVz9OCFZ/6qMCQGOb
qaGwHmUK6xzpUbbacnYrIM6nLSkXgOAwv7XXCojvY614ILTK3iXiLBOxPu5Eu13k
eUz9sHyD6vkgZzjtxXECQAkp4Xerf5TGfQXGXhxIX52yH+N2LtujCdkQZjXAsGdm
B2zNzvrlgRmgBrklMTrMYgm1NPcW+bRLGcwgW2PTvNM=
-----END RSA PRIVATE KEY-----
)";
    auto publicKey = R"(
-----BEGIN PUBLIC KEY-----
MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQC8kGa1pSjbSYZVebtTRBLxBz5H
4i2p/llLCrEeQhta5kaQu/RnvuER4W8oDH3+3iuIYW4VQAzyqFpwuzjkDI+17t5t
0tyazyZ8JXw+KgXTxldMPEL95+qVhgXvwtihXC1c5oGbRlEDvDF6Sa53rcFVsYJ4
ehde/zUxo6UvS7UrBQIDAQAB
-----END PUBLIC KEY-----
)";

    GIVEN("An encoded payload using a private key") {
        auto encoded = jwt::encode(payload, privateKey, "RS512");

        WHEN("it is decoded using a public key") {
            auto decoded = jwt::decode(encoded, publicKey, { "RS512" });

            THEN("it equals the payload") {
                REQUIRE(decoded == payload);
            }
        }

        WHEN("it is auto decoded with no algorithms specified") {
            auto decoded = jwt::decode(encoded, publicKey);

            THEN("the algorithm is determined by the token and properly decoded") {
                REQUIRE(decoded == payload);
            }
        }

        WHEN("it is decoded with the wrong algorithms specified") {
            auto decoded = jwt::decode(encoded, publicKey, { "RS256" });

            THEN("it returns null") {
                REQUIRE(decoded == nullptr);
            }
        }
    }
}

SCENARIO("JWT's can be encoded and decoded using ES256") {
    auto payload = R"(
        {
            "sub": "1234567890",
            "name": "John Doe",
            "admin": true
        }
    )"_json;
    auto privateKey = R"(
-----BEGIN EC PRIVATE KEY-----
MIHbAgEBBEGPWb0IqNdCUE270P42PYnRIkqZSaXB9kkWDQkfENA3sTM5Uu+5ZF+B
Wk336PYnNocbvtXUSl3x+1wNyw6Nbp0qpaAHBgUrgQQAI6GBiQOBhgAEAEf2nD9L
RWnmqUSFhaT7AKXEWIhXOTr5s5UXCayDc0oUQR2SrnyevwNvlzarmBE6qZx2MFxS
paPzXtGbPKSn89BMAD+v84XQhyzwA2j0/IISkp+JJyCk3FK4/GqW7ZIhGfu8LZbc
hxGofNuXUwkni7KTi3w0zeEtZSVlFWTdZqCuIdGi
-----END EC PRIVATE KEY-----
)";
    auto publicKey = R"(
-----BEGIN PUBLIC KEY-----
MIGbMBAGByqGSM49AgEGBSuBBAAjA4GGAAQAR/acP0tFaeapRIWFpPsApcRYiFc5
OvmzlRcJrINzShRBHZKufJ6/A2+XNquYETqpnHYwXFKlo/Ne0Zs8pKfz0EwAP6/z
hdCHLPADaPT8ghKSn4knIKTcUrj8apbtkiEZ+7wtltyHEah825dTCSeLspOLfDTN
4S1lJWUVZN1moK4h0aI=
-----END PUBLIC KEY-----
)";

    GIVEN("An encoded payload using a private key") {
        auto encoded = jwt::encode(payload, privateKey, "ES256");

        WHEN("it is decoded using a public key") {
            auto decoded = jwt::decode(encoded, publicKey, { "ES256" });

            THEN("it equals the payload") {
                REQUIRE(decoded == payload);
            }
        }

        WHEN("it is auto decoded with no algorithms specified") {
            auto decoded = jwt::decode(encoded, publicKey);

            THEN("the algorithm is determined by the token and properly decoded") {
                REQUIRE(decoded == payload);
            }
        }

        WHEN("it is decoded with the wrong algorithms specified") {
            auto decoded = jwt::decode(encoded, publicKey, { "ES384" });

            THEN("it returns null") {
                REQUIRE(decoded == nullptr);
            }
        }
    }
}

SCENARIO("JWT's can be encoded and decoded using ES384") {
    auto payload = R"(
        {
            "sub": "1234567890",
            "name": "John Doe",
            "admin": true
        }
    )"_json;
    auto privateKey = R"(
-----BEGIN EC PRIVATE KEY-----
MIHbAgEBBEGPWb0IqNdCUE270P42PYnRIkqZSaXB9kkWDQkfENA3sTM5Uu+5ZF+B
Wk336PYnNocbvtXUSl3x+1wNyw6Nbp0qpaAHBgUrgQQAI6GBiQOBhgAEAEf2nD9L
RWnmqUSFhaT7AKXEWIhXOTr5s5UXCayDc0oUQR2SrnyevwNvlzarmBE6qZx2MFxS
paPzXtGbPKSn89BMAD+v84XQhyzwA2j0/IISkp+JJyCk3FK4/GqW7ZIhGfu8LZbc
hxGofNuXUwkni7KTi3w0zeEtZSVlFWTdZqCuIdGi
-----END EC PRIVATE KEY-----
)";
    auto publicKey = R"(
-----BEGIN PUBLIC KEY-----
MIGbMBAGByqGSM49AgEGBSuBBAAjA4GGAAQAR/acP0tFaeapRIWFpPsApcRYiFc5
OvmzlRcJrINzShRBHZKufJ6/A2+XNquYETqpnHYwXFKlo/Ne0Zs8pKfz0EwAP6/z
hdCHLPADaPT8ghKSn4knIKTcUrj8apbtkiEZ+7wtltyHEah825dTCSeLspOLfDTN
4S1lJWUVZN1moK4h0aI=
-----END PUBLIC KEY-----
)";

    GIVEN("An encoded payload using a private key") {
        auto encoded = jwt::encode(payload, privateKey, "ES384");

        WHEN("it is decoded using a public key") {
            auto decoded = jwt::decode(encoded, publicKey, { "ES384" });

            THEN("it equals the payload") {
                REQUIRE(decoded == payload);
            }
        }

        WHEN("it is auto decoded with no algorithms specified") {
            auto decoded = jwt::decode(encoded, publicKey);

            THEN("the algorithm is determined by the token and properly decoded") {
                REQUIRE(decoded == payload);
            }
        }

        WHEN("it is decoded with the wrong algorithms specified") {
            auto decoded = jwt::decode(encoded, publicKey, { "ES512" });

            THEN("it returns null") {
                REQUIRE(decoded == nullptr);
            }
        }
    }
}

SCENARIO("JWT's can be encoded and decoded using ES512") {
    auto payload = R"(
        {
            "sub": "1234567890",
            "name": "John Doe",
            "admin": true
        }
    )"_json;
    auto privateKey = R"(
-----BEGIN EC PRIVATE KEY-----
MIHbAgEBBEGPWb0IqNdCUE270P42PYnRIkqZSaXB9kkWDQkfENA3sTM5Uu+5ZF+B
Wk336PYnNocbvtXUSl3x+1wNyw6Nbp0qpaAHBgUrgQQAI6GBiQOBhgAEAEf2nD9L
RWnmqUSFhaT7AKXEWIhXOTr5s5UXCayDc0oUQR2SrnyevwNvlzarmBE6qZx2MFxS
paPzXtGbPKSn89BMAD+v84XQhyzwA2j0/IISkp+JJyCk3FK4/GqW7ZIhGfu8LZbc
hxGofNuXUwkni7KTi3w0zeEtZSVlFWTdZqCuIdGi
-----END EC PRIVATE KEY-----
)";
    auto publicKey = R"(
-----BEGIN PUBLIC KEY-----
MIGbMBAGByqGSM49AgEGBSuBBAAjA4GGAAQAR/acP0tFaeapRIWFpPsApcRYiFc5
OvmzlRcJrINzShRBHZKufJ6/A2+XNquYETqpnHYwXFKlo/Ne0Zs8pKfz0EwAP6/z
hdCHLPADaPT8ghKSn4knIKTcUrj8apbtkiEZ+7wtltyHEah825dTCSeLspOLfDTN
4S1lJWUVZN1moK4h0aI=
-----END PUBLIC KEY-----
)";

    GIVEN("An encoded payload using a private key") {
        auto encoded = jwt::encode(payload, privateKey, "ES512");

        WHEN("it is decoded using a public key") {
            auto decoded = jwt::decode(encoded, publicKey, { "ES512" });

            THEN("it equals the payload") {
                REQUIRE(decoded == payload);
            }
        }

        WHEN("it is auto decoded with no algorithms specified") {
            auto decoded = jwt::decode(encoded, publicKey);

            THEN("the algorithm is determined by the token and properly decoded") {
                REQUIRE(decoded == payload);
            }
        }

        WHEN("it is decoded with the wrong algorithms specified") {
            auto decoded = jwt::decode(encoded, publicKey, { "ES256" });

            THEN("it returns null") {
                REQUIRE(decoded == nullptr);
            }
        }
    }
}