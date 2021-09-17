#include <gtest/gtest.h>
#include <processmanager.h>

#include <unistd.h> // fork()

TEST(ProcessManager, PidTest)
{
    ProcessManager p;

    int pid = p.getProcessId("init");

    EXPECT_EQ(pid, 1); // init process has pid 1
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}