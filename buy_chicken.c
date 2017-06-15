/*
 * > File Name: buy_chicken.c
 * > Author: Jack Kang
 * > Mail: kangyijie@xiyoulinux.org
 * > Created Time: 2017年06月12日 星期一 21时22分54秒
 */

#include <stdio.h>
int main(void)
{
    if(order_chicken() == true){
        while(1){
            if(look_chicken() == true){
                eat_chicken();
                return true;
            }else
                play_phone(3);
        }
    }else {
        buy_other();
        return true;
    }
    //xuqiubianle
    if(order_chicken() == true){
        while(1){
            if(look_chicken() == true){
                eat_chicken();
                return true;
            }else
                if(play_phone(3) == NO_POWER){
                    buy_other();
                    return true;
                }
                
        }
    }else {
        buy_other();
        return true;
    }

    switch(state){

        case ORDER:
            if(order_chicken() == true) {
                state = LOOK;
                break;
            }else {
                state = OTHER;
                break;
            }

        case LOOK:
            if(look_chicken() == true){
                state = EAT;
                break;
            }else{
                state = PHONE;
                break;
            }

        case PHONE:
            play_phone(3)
            state = LOOK;
            break;

        case OTHER:
            buy_other();
            state = EAT;

        case EAT:
            return true;
    }

   switch(state){

        case ORDER:
            if(order_chicken() == true) {
                state = LOOK;
                break;
            }else {
                state = OTHER;
                break;
            }

        case LOOK:
            if(look_chicken() == true){
                state = EAT;
                break;
            }else{
                state = PHONE;
                break;
            }

        case PHONE:
            if(play_phone(3) == NO_POWER){
                state = OTHER;
            }else
                state = LOOK;
            break;

        case OTHER:
            buy_other();
            state = EAT;

        case EAT:
            return true;
    }
