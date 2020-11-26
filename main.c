#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
typedef struct character{
    int HP,MP,horcrux,HPmax;
    bool cloak,elderWand;
}hero;
bool checkHorcrux(hero *name,int n){
    if (name->horcrux == n)
        return true;
    else return false;
}
bool checkHP(hero *name){
    if (name->HP <= 0)
        return true;
    else return false;
}
int fight(hero *name,int i, int R,int event[]){
    int h1 = (i+1) % (100+R);
    int h2 = event[i] % (100+R);
    if (h1 >= h2)
        return 1;
    else if (name->cloak)
        return -1;
    else return 0;
}
void deadEater(hero *name,int i, int R, int event[]){
    if (fight(name,i,R,event)== 0)
        name->HP = name->HP - event[i];
    else if(fight(name,i,R,event) == 1){
        if(999-(name->MP) >= event[i])
            name->MP = name->MP + event[i];
        else
            name->MP = 999;
    }
}
void regen(hero *name, int R){
    if(name->HPmax - name->HP >= name->MP){
        name->HP = name->HP + name->MP;
        name->MP = 0;
    }else{
        name->MP = name->MP - (name->HPmax - name->HP);
        name->HP = name->HPmax;
    }
}
void evadeMuggle(hero *name,int *i,int event[]){
    if(!name->cloak){
        int f = name->MP - (event[(*i)] % 100);
        if (f > 4){
            if (sqrt(f) == round(sqrt(f))){
                    name->MP = (round(sqrt(f)) - 1)*(round(sqrt(f)) - 1);
                }
            else
                name->MP = floor(sqrt(f))*floor(sqrt(f));
        }
        else{
            if (*i < 2)
                *i = -2;
            else{
                event[(*i)] = -1;
                *i = *i -3;
            }
        }
    }
}
void faceSphinx(hero *name,int i, int R, int event[]){
    if (!name->cloak){
        if (fight(name,i,R,event) == 0)
            name->horcrux = 0;
        else
            name->cloak = true;
    }
}
bool isPrime(int x){
    if(x < 2)
        return false;
    else if(x < 4)
        return true;
    else
        for(int i = 2; i < sqrt(x); i++)
            if(x % i == 0)
                return false;
    return true;
}
int checkGiant(int i, int event[]){
    int x = event[i] % 100;
    for(int i = x/2; i > 1; i++){
        if (x % i == 0){
            if (isPrime(i))
                return i;
        }
    }
    return 1;
}
void faceGiant(hero *name,int i, int R, int event[]){
    if(!name->cloak){
       if(fight(name,i,R,event)==0){
            name->HP = name->HP - event[i];
            name->MP = name->MP - checkGiant(i,event);
       }
    }
}
int checkConsecutive(int i, int event[], int length){
    int offsetLeft = 1, offsetRight = 1,offsetMax = 1;
    for(int i = 0; i < length; i++){
        for(int j = 0; j < length ;j++){
            if (i != j){
                if(event[i] - offsetLeft == event[j])
                    offsetLeft++;
                else if(event[i] + offsetRight == event[j])
                    offsetRight++;
            }
        }
        if(offsetLeft + offsetRight - 1 > offsetMax)
            offsetMax = offsetLeft + offsetRight - 1;
        offsetLeft = 1;
        offsetRight = 1;
    }
    return offsetMax;
}
void bellatrixLestrange(hero *name,int R, int i, int event[],int length){
    if(!name->cloak){
        if (fight(name,i,R,event) == 0){
            name->HP = name->HP - event[i];
            if(name->horcrux <= checkConsecutive(i,event,length))
                name->horcrux = 0;
            else
                name->horcrux = name->horcrux - checkConsecutive(i,event,length);
        }
        else {
            if(999-name->MP >= event[i])
                name->MP = name->MP + event[i];
            else
                name->MP = 999;
            name->horcrux--;
        }
    }
}
int fibonacci(int x){
    int f, f1=1, f2=1;
    if (x <= 2)
        return 1;
    else
        while(f1 + f2 < x){
            f = f1 + f2;
            f1 = f2;
            f2 = f;
        }
    return f;
}
void severusSnape(hero *name){
    if(!name->cloak){
        name->HP = fibonacci(name->HP);
    }
}
bool checkFibo(int x){
    int f1 = 1, f2 = 1, f = f1 + f2;
    if(x == 0)
        return false;
    else if(x < 4)
        return true;
    while(f < x){
        f1 = f2;
        f2 = f;
        f = f1 + f2;
    }
    if(f == x)
        return true;
    else
        return false;
}
void faceVoldemort(hero *name,int i, int R, int event[]){
    if(checkFibo(i)){
        if(fight(name,i,R,event) == 1){
            name->MP = 999;
            name->HP = name->HPmax;
        }
        else
            name->HP = -1;
    } else
        name->HP = -1;
}
int harryDeadEater(hero *name,int i, int R, int event[]){
    int h1 = (i+1) % (100+R);
    int h2 = event[i] % (100+R);
    if ((h2 > h1)&&(h2 > name->MP)&&(isPrime(h2))){
        if(name->cloak)
            return -1;
        else
            return 0;
    }
    else
        return 1;
}
void harryFightDeadEater(hero *name,int i, int R, int event[]){
    if (harryDeadEater(name,i,R,event)== 0)
        name->HP = name->HP - event[i];
    else if(harryDeadEater(name,R,i,event) == 1){
        if(999-name->MP >= event[i])
            name->MP = name->MP + event[i];
        else
            name->MP = 999;
    }
}
void harrySnape(hero *name){
    if(!name->cloak){
        name->HP = name->HPmax;
        name->MP = 999;
        name->elderWand = true;
    }
}
void harryFaceVoldemort(hero *name,int i, int R, int event[]){
    if(name->elderWand){
        name->HP = name->HPmax;
        name->MP = 999;
    }else{
        if(checkFibo(i)){
            if(fight(name,R,i,event) == 1){
                name->MP = 999;
                name->HP = name->HPmax;
            }
            else
                name->HP = -1;
        }else
            name->HP = -1;
    }
}
int findPrime(int x){
    for (int i = x - 1; i > 1; i++)
    if(isPrime(i))
        return i;
    return 0;
}
void ronRegen(hero *name, int R){
    if (R >= 3){
        int P = findPrime(R), HPregen = name->MP / P;
        if(name->HPmax - name->HP >= HPregen){
            name->HP = name->HP + HPregen;
            name->MP = name->MP - HPregen*P;
        }else{
            name->MP = name->MP - (name->HPmax - name->HP)*P;
            name->HP = name->HPmax;
        }
    }
}
int gcd(int a, int b) {
    int tmp;
    while(b != 0) {
        tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}
void girlsfaceGiant(hero *name,int i, int R, int event[]){
    if(gcd(name->HP,event[i] % 100) != 1){
        faceGiant(name,i,R,event);
    }
}
void getInfor(int *R, int *N, int *ID, int *m, int event[], int *length){
    char c;
    scanf("%d%d%d%d",R,N,ID,m);
    do{
        scanf("%d",&event[(*length)]);
        (*length)++;
        c = getchar();
    }while(c!='\n');
}
int journey(int R, int N, int ID, int m, int event[], int length){
    getInfor(&R,&N,&ID,&m,event,&length);
    hero data;
    hero *name;
    name = &data;
    switch(ID){
        case 1:{
            name->HP = 999;
            name->HPmax = 999;
            name->MP = m;
            name->horcrux = 0;
            int i = 0;
            do{
                int step = event[i] / 100;
                if(step == 1){
                    harryFightDeadEater(name,i,R,event);
                    if (checkHP(name)){
                        return -1;
                    }
                }
                else if(step == 2)
                    evadeMuggle(name,&i,event);
                else if(step == 3)
                    faceSphinx(name,i,R,event);
                else if(step == 5){
                    faceGiant(name,i,R,event);
                    if (checkHP(name)){
                        return -1;
                    }
                }
                else
                switch(event[i]){
                    case 0:
                        name->horcrux++;
                        if(checkHorcrux(name,N)){
                            return name->HP+name->MP;
                        }
                        break;
                    case 1:
                        regen(name,R);
                        break;
                    case 666:
                        bellatrixLestrange(name,R,i,event,length);
                        if (checkHP(name)){
                            return -1;
                        }
                        break;
                    case 777:
                        harrySnape(name);
                        break;
                    case 999:
                        harryFaceVoldemort(name,i,R,event);
                        if (checkHP(name)){
                            return -1;
                        }
                        break;
                }
                i++;
            }while((i < length)&&(i > -1));
            return 0;
            break;
        }
        case 2:{
            name->HP = 900;
            name->HPmax = 900;
            name->MP = m;
            name->horcrux = 0;
            int i = 0;
            do{
                int step = event[i] / 100;
                if(step == 1){
                    deadEater(name,i,R,event);
                    if (checkHP(name)){
                        return -1;
                    }
                }
                else if(step == 2)
                    evadeMuggle(name,&i,event);
                else if(step == 3)
                    faceSphinx(name,i,R,event);
                else if(step == 5){
                    girlsfaceGiant(name,i,R,event);
                    if (checkHP(name)){
                        return -1;
                    }
                }
                else
                switch(event[i]){
                    case 0:
                        name->horcrux++;
                        if(checkHorcrux(name,N)){
                           return name->HP+name->MP;
                        }
                        break;
                    case 1:
                        regen(name,R);
                        break;
                    case 666:
                        bellatrixLestrange(name,R,i,event,length);
                        if (checkHP(name)){
                            return -1;
                        }
                        break;
                    case 777:
                        severusSnape(name);
                        break;
                    case 999:
                        faceVoldemort(name,i,R,event);
                        if (checkHP(name)){
                            return -1;
                        }
                        break;
                }
                i++;
            }while((i < length)&&(i > -1));
            return 0;
            break;
        }
        case 3:{
            name->HP = 888;
            name->HPmax = 888;
            name->MP = m;
            name->horcrux = 0;
            int i = 0;
            do{
                int step = event[i] / 100;
                if(step == 1){
                    deadEater(name,i,R,event);
                    if (checkHP(name)){
                        return -1;
                    }
                }
                else if(step == 2)
                    evadeMuggle(name,&i,event);
                else if(step == 3)
                    faceSphinx(name,i,R,event);
                else if(step == 5){
                    girlsfaceGiant(name,i,R,event);
                    if (checkHP(name)){
                        return -1;
                    }
                }
                else
                switch(event[i]){
                    case 0:
                        name->horcrux++;
                        if(checkHorcrux(name,N)){
                            return name->HP+name->MP;
                        }
                        break;
                    case 1:
                        ronRegen(name,R);
                        break;
                    case 666:
                        bellatrixLestrange(name,R,i,event,length);
                        if (checkHP(name)){
                            return -1;
                        }
                        break;
                    case 777:
                        severusSnape(name);
                        break;
                    case 999:
                        faceVoldemort(name,i,R,event);
                        if (checkHP(name)){
                            return -1;
                        }
                        break;
                }
                i++;
            }while((i < length)&&(i > -1));
            return 0;
            break;
        }
        case 4:{
            name->HP = 777;
            name->HPmax = 777;
            name->MP = m;
            name->horcrux = 0;
            int i = 0;
            do{
                int step = event[i] / 100;
                if(step == 1){
                    deadEater(name,i,R,event);
                    if (checkHP(name)){
                        return -1;
                    }
                }
                else if(step == 2)
                    evadeMuggle(name,&i,event);
                else if(step == 3)
                    faceSphinx(name,i,R,event);
                else if(step == 5){
                    girlsfaceGiant(name,i,R,event);
                    if (checkHP(name)){
                        return -1;
                    }
                }
                else
                switch(event[i]){
                    case 0:
                        name->horcrux++;
                        if(checkHorcrux(name,N)){
                            return name->HP+name->MP;
                        }
                        break;
                    case 1:
                        ronRegen(name,R);
                        break;
                    case 666:
                        bellatrixLestrange(name,R,i,event,length);
                        if (checkHP(name)){
                            return -1;
                        }
                        break;
                    case 777:
                        return -1;
                        break;
                    case 999:
                        faceVoldemort(name,i,R,event);
                        if (checkHP(name)){
                           return -1;
                        }
                        break;
                }
                i++;
            }while((i < length)&&(i > -1));
            return 0;
            break;
        }
    }
    return 0;
}
int main()
{
    int R=0,N=0,ID=0,m=0,size = 0,arr[1000];
    return journey(R,N,ID,m,arr,size);

}
