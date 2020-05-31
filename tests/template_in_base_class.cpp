#include <gtest/gtest.h>

#include <memory>

class lapi_message
{
};
class geofence_protocol_buffer
{
};

class deserializer
{
public:
    template <typename Deserialized, typename Message>
    std::unique_ptr<Deserialized> deserialize(Message &message)
    {
        return std::make_unique<Deserialized>();
    }
};

class lapi_message_to_geofence_protocol_buffer_deserializer : public deserializer
{
};

TEST(special_deserializer, should_compile)
{
    lapi_message_to_geofence_protocol_buffer_deserializer deserializer_for_test;

    lapi_message message_for_test;
    auto result = deserializer_for_test.deserialize<geofence_protocol_buffer, lapi_message>(message_for_test);
}