
#include "SignalBus/SignalBus.h"
#include "SignalBus/Signals/Signals.h"

#include "gtest/gtest.h"
class SignalBusTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        SignalBus::create();
    }

    void TearDown() override
    {
    }

    SignalBus &getBus()
    {
        return SignalBus::get();
    }
};

TEST_F(SignalBusTest, SingletonPatternWorks)
{
    EXPECT_NO_THROW(SignalBus::create());
    EXPECT_NO_THROW(SignalBus::get());

    SignalBus &bus1 = SignalBus::get();
    SignalBus &bus2 = SignalBus::get();
    EXPECT_EQ(&bus1, &bus2);
}

TEST_F(SignalBusTest, SubscribeAndPublishGoldChangedSignal)
{
    unsigned int receivedValue  = 0;
    bool         callbackCalled = false;

    auto callback = [&](const GoldChangedSignal &signal)
    {
        receivedValue  = signal.m_value;
        callbackCalled = true;
    };

    getBus().subscribe<GoldChangedSignal>(callback);

    GoldChangedSignal signal(150);
    getBus().publish(signal);

    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(receivedValue, 150);
}

TEST_F(SignalBusTest, MultipleSubscribersForSameSignal)
{
    int          callback1Count = 0;
    int          callback2Count = 0;
    unsigned int lastValue1     = 0;
    unsigned int lastValue2     = 0;

    auto callback1 = [&](const GoldChangedSignal &signal)
    {
        callback1Count++;
        lastValue1 = signal.m_value;
    };

    auto callback2 = [&](const GoldChangedSignal &signal)
    {
        callback2Count++;
        lastValue2 = signal.m_value;
    };

    getBus().subscribe<GoldChangedSignal>(callback1);
    getBus().subscribe<GoldChangedSignal>(callback2);

    GoldChangedSignal signal(200);
    getBus().publish(signal);

    EXPECT_EQ(callback1Count, 1);
    EXPECT_EQ(callback2Count, 1);
    EXPECT_EQ(lastValue1, 200);
    EXPECT_EQ(lastValue2, 200);
}

TEST_F(SignalBusTest, UnsubscribeFromSignal)
{
    int callbackCount = 0;

    auto callback = [&](const GoldChangedSignal &signal)
    {
        callbackCount++;
    };

    getBus().subscribe<GoldChangedSignal>(callback);

    GoldChangedSignal signal1(100);
    getBus().publish(signal1);
    EXPECT_EQ(callbackCount, 1);

    getBus().unsubscribeAll<GoldChangedSignal>(callback);

    GoldChangedSignal signal2(200);
    getBus().publish(signal2);
    EXPECT_EQ(callbackCount, 1);
}

TEST_F(SignalBusTest, PublishWithoutSubscribers)
{
    GoldChangedSignal signal(300);
    EXPECT_NO_THROW(getBus().publish(signal));
}

TEST_F(SignalBusTest, SequentialSignalsWithDifferentValues)
{
    std::vector<unsigned int> receivedValues;

    auto callback = [&](const GoldChangedSignal &signal)
    {
        receivedValues.push_back(signal.m_value);
    };

    getBus().subscribe<GoldChangedSignal>(callback);

    getBus().publish(GoldChangedSignal(10));
    getBus().publish(GoldChangedSignal(20));
    getBus().publish(GoldChangedSignal(30));

    EXPECT_EQ(receivedValues.size(), 3);
    EXPECT_EQ(receivedValues[0], 10);
    EXPECT_EQ(receivedValues[1], 20);
    EXPECT_EQ(receivedValues[2], 30);
}

TEST_F(SignalBusTest, LambdaWithContextCapture)
{
    struct TestContext
    {
        unsigned int gold    = 0;
        bool         updated = false;
    };

    TestContext context;

    auto callback = [&context](const GoldChangedSignal &signal)
    {
        context.gold    = signal.m_value;
        context.updated = true;
    };

    getBus().subscribe<GoldChangedSignal>(callback);

    GoldChangedSignal signal(999);
    getBus().publish(signal);

    EXPECT_TRUE(context.updated);
    EXPECT_EQ(context.gold, 999);
}

TEST_F(SignalBusTest, SignalTypeIsCorrect)
{
    std::string receivedType;

    auto callback = [&]([[maybe_unused]] const GoldChangedSignal &signal)
    {
        receivedType = typeid(signal).name();
    };

    getBus().subscribe<GoldChangedSignal>(callback);

    GoldChangedSignal signal(123);
    getBus().publish(signal);

    EXPECT_FALSE(receivedType.empty());
}

TEST_F(SignalBusTest, MultipleSubscribeUnsubscribe)
{
    int callCountA = 0;
    int callCountB = 0;

    auto callbackA = [&](const GoldChangedSignal &signal)
    { callCountA++; };
    auto callbackB = [&](const GoldChangedSignal &signal)
    { callCountB++; };

    getBus().subscribe<GoldChangedSignal>(callbackA);
    getBus().publish(GoldChangedSignal(1));
    EXPECT_EQ(callCountA, 1);

    getBus().subscribe<GoldChangedSignal>(callbackB);
    getBus().publish(GoldChangedSignal(2));
    EXPECT_EQ(callCountA, 2);
    EXPECT_EQ(callCountB, 1);

    getBus().unsubscribeAll<GoldChangedSignal>(callbackA);
    getBus().publish(GoldChangedSignal(3));
    EXPECT_EQ(callCountA, 2);
    EXPECT_EQ(callCountB, 1);
}