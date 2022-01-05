#ifndef RANDOM_H
#define RANDOM_H
/*  https://github.com/marin9/MOS/blob/master/include/rand.h
    https://www.riscosopen.org/forum/forums/11/topics/15091
    https://forums.raspberrypi.com/viewtopic.php?t=196015
    BCM2835 芯片上有一个未公开的随机数生成器
    似乎质量很好——通过了FIPS 140-2 和 Dieharder 随机性测试
*/
void rand_init();
int rand_get();
#endif