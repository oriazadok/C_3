
#include <stdio.h> 
#include <string.h> 
#include "my_string.h"

char _txt[TXT+1];
char _word[WORD+1];

int check(int j, int bo);
int Gematr_print();
int Atbash_print(char t[],char w[],char rv_w[]);

int containIndex();
int contain();

/////////////1//////////////////////////
int GematriaSequences() {
    char ch = 0;
    for(int i=0; i<WORD; i++) {
        scanf("%c",&ch);
        if(!ch || ch == ' ' || ch == '\n' || ch == '\t') {
                _word[i] = '\0';
                word[i] = '\0';
                break;
            }
            _word[i] = ch;
            word[i] = ch;
            if(_word[i] >= 'a' && 'z' >= _word[i]) {
                _word[i]-=32;
            }
            if(_word[i] >= 'A' && 'Z' >= _word[i]) {
                sum += (_word[i]-('A'-1));
            }
    }
    word[WORD]='\0';
    _word[WORD]='\0';


    int pass = 0;
    for(int i=0; i<TXT; i++) {
        if(scanf("%c",&ch) == EOF) {
            break;
        }
        if(pass == 0) {
            txt[i] = ch;
            _txt[i] = ch;
        }
            
        if((ch == '~') || (pass == 1)) {
            pass = 1;
            continue;
        }
            
        if(_txt[i]>='a'&&'z'>=_txt[i]) {
            _txt[i]-=32;
        }
    }
    txt[TXT]='\0';
    _txt[TXT]='\0';
    printf("Gematria Sequences: ");  
    Gematr_print();
    printf("\n");
        return 0;
}

////////////////1a////////////////////
int check(int j, int bo) {
    int k = 0;
    int sum_txt = 0;
    for(int i=j; i<TXT && txt[i] !='~'; i++) {
            
        if(_txt[i] >= 'A' && 'Z' >= _txt[i]) {    // original 'Z' > _txt[i]
            sum_txt += (_txt[i] - ('A'-1));
        }
        if(sum_txt == sum) {
            if(bo) {
                k=j;
                printf("%c",txt[k]);
                while(k != i) {
                    printf("%c",txt[++k]);
                }
            }

            return 1;
        }
        if(sum_txt > sum) {
            return 0;
        }
    }
    return 0;

}

/////////////////////1b////////////////////
int Gematr_print() {  

    int bo = 0;
    for(int i=0; i<TXT && txt[i] != '~'; i++) {
        if(_txt[i] >= 'A' && 'Z' >= _txt[i] && check(i,0)) {    
            if(bo) {
                printf("~");
                check(i,1);
            }
            else {
                check(i,1);
                bo = 1;  
            }
        }
    } 
    return 0;

}

///////////////////2//////////////////////
int AtbashSequences() {
    char atbash[strlen(_txt)+1];
    strcpy(atbash,_txt);
    atbash[strlen(_txt)] = '\0';
    for(int i=0; i<TXT && txt[i] != '~'; i++) {

        if(atbash[i] >= 'A' && 'Z' >= atbash[i]) {
            atbash[i] = ('Z'-(atbash[i]-'A'));
        }
    }
    char rvers_word[strlen(word)+1];
    for (int i = 0,length=strlen(_word)-1; length>=0; i++,length--) {
        rvers_word[i] = _word[length];
    }
    rvers_word[strlen(word)] = '\0';
    printf("Atbash Sequences: ");    
    Atbash_print(atbash, _word, rvers_word);
    printf("\n");

    return 0;
}

//////////////////2a////////////////////
int Atbash_print(char t[],char w[],char rv_w[]) {
    char ans[TXT+1] = "";
    char lm[] = "~";
    int sum = 0;
    for(int i=0; i<TXT && t[i] != '~'; i++) {
        if(t[i] == ' ') {
            continue;
        }

        if(t[i] == w[0]) {
            int som = strlen(rv_w);
            int bo = 0;
            char pr[TXT];
            int k = 0;
            for(int j=0, ii=i; j<strlen(rv_w) && t[ii] != '~'; j++, k++, ii++) {
                bo = 1;
                pr[k] = txt[ii];
                som--;
                if(t[ii] == ' ') {
                    som++;
                    j--;
                    continue;
                        
                }
                if(t[ii] != w[j]){
                    bo = 0;
                    break;
                }
            }
            pr[k] = '\0';
            if(bo && som == 0) {
                sum += 1+strlen(pr);
                strcat(ans,lm);
                strcat(ans,pr);
            }
        }
        if(t[i] == rv_w[0]) {
            int som = strlen(rv_w);
            int bo = 0;
            char pr[TXT];
            int k = 0;
            for(int j=0,ii=i; j<strlen(rv_w) && t[ii] != '~'; j++, k++, ii++) {
                bo = 1;
                pr[k] = txt[ii];
                som--;
                if(txt[ii] == ' '){
                    j--;
                    som++;
                    continue;
                }
                if(t[ii] != rv_w[j]){
                    bo = 0;
                    break;
                }
            }
            pr[k] = '\0';
            if(bo && !som) {
                sum += 1+strlen(pr);
                strcat(ans,lm);
                strcat(ans,pr);
            }
        }

    }
    ans[sum] = '\0';
    for(int i=1; i<strlen(ans); i++){
        printf("%c",ans[i]);
    }

    return 0;
}

int AnagramSequences() {
    char ans[TXT+1] = "";
    printf("Anagram Sequences: ");

    int wordLength = strlen(word);
    int sumOfWord = 0;

    for(int i=0; i < wordLength; i++) {
        sumOfWord += (int)(_word[i]);
    }

    for(int i=0; i<TXT && txt[i] != '~'; i++) {
        if((_txt[i] < 'A') || ('Z' < _txt[i])) {
            continue;
        }
        
        if(containIndex(i, wordLength) == 1) {
            
            int sum = 0;
            int len = 0;
            int d = 0;
            for(int j=i; j < (i+wordLength+d) && _txt[j] != '~'; j++, len++) {
                if(_txt[j] != ' ') {
                    sum += (int)(_txt[j]);
                }
                else {
                    d++;
                }

                if ((_txt[j] == '-') || (_txt[j] == ',')) {
                    break;
                }
            }

            if(sumOfWord == sum) {
                if(contain(i, len, wordLength) == 1) {
                    char temp[len + 1];
                    memcpy(temp, &txt[i], len);
                    strcat(ans,temp);
                    strcat(ans, "~");
                }
            }

        }
    }
    for(int i=0; i<strlen(ans)-1; i++) {
        printf("%c", ans[i]);
    }
                    

    printf("\n");
    return 0;
}

int containIndex(int index, int wordLength) {
    for(int i=0; i < wordLength; i++) {
        if(_txt[index] == _word[i]) {
            return 1;
        }
    }
    return 0;
}

int contain(int i, int k, int wordLength) {

    char subtext[k+1];
    memcpy(subtext, &_txt[i], k);
    subtext[k] = '\0';

    int numOfZero = 0;
    for (int i=0; i<wordLength; i++) {
        for(int j=0; j<k; j++) {
            if(subtext[j] == _word[i]) {
                subtext[j] = 0;
                numOfZero++;
                break;
            }
        }
    }
    if(numOfZero == wordLength) {
        return 1;
    }

    return 0;
}
