#include<iostream>
#include<thread>
#include<mutex>


std::mutex mtx;
int value =0;
//вмене в котелку нічого окрім цього не стрельнуло(─‿‿─)
template <typename T0, typename T1, typename T2>
void Threadaddition(T0 frst,T1 scnd,T2 thrd)
{
    std::lock_guard<std::mutex> lockg(mtx);
    T0 result0 = frst+scnd+thrd;
}
template <typename T0, typename T1, typename T2>
void Threadmulti(T0 frst,T1 scnd,T2 thrd)
{
    std::lock_guard<std::mutex> lockg(mtx);
    T0 result1 = frst+scnd*thrd;
}

int main()
{
    std::thread t1(Threadaddition<std::string,int,float>,"Addition",32,17.28f);
    std::thread t2(Threadmulti<std::string,int,double>,"Multipli",-236,17.28);

    t1.join();
    t2.join();

   return 0;
}
