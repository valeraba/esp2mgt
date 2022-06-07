/*
Copyright © 2015, BVAgile. All rights reserved.
Contacts: <bvagile@gmail.com>
*/

#include"MgtClient.h"
#define le struct
#define lo __uint32
#define lb __uint8
#define lr void
#define lv const
#define l16 static
#define lc if
#define lh return
#define l29 memcpy
#define l72 while
#define l8 char
#define l232 unsigned
#define l11 int
#define l219 strlen
#define l527 strncmp
#define l33 for
#define l507 continue
#define l401 memset
#define l81 sizeof
#define ly else
#define l121 crc32
#define l77 __uint64
#define l111 union
#define l30 enum
#define l12 __uint16
#define l19 bool
#define l327 rand
#define lq false
#define l539 memcmp
#define l2 true
#define l535 strchr
#define l10 break
#define l250 typedef
#define l206 __int64
#define l130 __int16
#define l237 read
#define l281 abort
#define l419 __int8
#define l129 __int32
#define l312 float
#define l195 double
#define l148 switch
#define l6 case
#define l225 default
#define l362 updateTime
#define l238 open
#define l292 close
#define l3 m_signals
#define l132 rem
#define l107 getUTCTime
#define lt signal
#define l359 strrchr
#define l387 atoi
#define l343 memmove
#define l158 time
#define l397 shiftTime
#define l483 signal_updateInt
#define l90 Signal
#define l165 TimeStamp
#define l515 signal_updateDouble
#define l481 signal_updatePtr
#define l495 signal_updateTime
#define l548 mgt_init
#define l69 MgtClient
#define l484 DeviceConfig
#define l503 PortableSocket
#define l501 m_reserv
#define l528 mgt_start
#define l526 WayTransfer
#define l467 mgt_stop
#define l119 MgtState
#define l473 mgt_run
#define l447 mgt_getState
#define l489 mgt_send
#define l480 mgt_eventSend
#define l306 Event
#define l479 va_list
#define l450 va_start
#define l391 va_arg
#define l491 va_end
#define l471 mgt_eventBegin
#define l546 mgt_eventEnd
#define l452 mgt_readAns
#define l425 ErrorCode
#define l523 mgt_writeAns
#define l504 mgt_createSignal
#define l519 SignalType
#define l529 ChunkedTransfer
#define l537 mgt_attachSignal
#define l493 mgt_detachAll


le l115{lo l82[2];lo l23[4];lb l263[64];};lr l141(le l115*lz);lr l41(
le l115*lz,lv lb*l13,lo l54);lr l144(lb l57[16],le l115*lz);lr l141(
le l115*lz){lz->l82[0]=0;lz->l82[1]=0;lz->l23[0]=0x67452301;lz->l23[1
]=0xEFCDAB89;lz->l23[2]=0x98BADCFE;lz->l23[3]=0x10325476;}l16 lr l316
(le l115*lz,lv lb ls[64]){lo ld[16],lk,li,lg,lj;{(ld[0])=((lo)(ls)[(0
)])|((lo)(ls)[(0)+1]<<8)|((lo)(ls)[(0)+2]<<16)|((lo)(ls)[(0)+3]<<24);
};{(ld[1])=((lo)(ls)[(4)])|((lo)(ls)[(4)+1]<<8)|((lo)(ls)[(4)+2]<<16)|
((lo)(ls)[(4)+3]<<24);};{(ld[2])=((lo)(ls)[(8)])|((lo)(ls)[(8)+1]<<8)|
((lo)(ls)[(8)+2]<<16)|((lo)(ls)[(8)+3]<<24);};{(ld[3])=((lo)(ls)[(12)]
)|((lo)(ls)[(12)+1]<<8)|((lo)(ls)[(12)+2]<<16)|((lo)(ls)[(12)+3]<<24);
};{(ld[4])=((lo)(ls)[(16)])|((lo)(ls)[(16)+1]<<8)|((lo)(ls)[(16)+2]<<
16)|((lo)(ls)[(16)+3]<<24);};{(ld[5])=((lo)(ls)[(20)])|((lo)(ls)[(20)+
1]<<8)|((lo)(ls)[(20)+2]<<16)|((lo)(ls)[(20)+3]<<24);};{(ld[6])=((lo)(
ls)[(24)])|((lo)(ls)[(24)+1]<<8)|((lo)(ls)[(24)+2]<<16)|((lo)(ls)[(24
)+3]<<24);};{(ld[7])=((lo)(ls)[(28)])|((lo)(ls)[(28)+1]<<8)|((lo)(ls)[
(28)+2]<<16)|((lo)(ls)[(28)+3]<<24);};{(ld[8])=((lo)(ls)[(32)])|((lo)(
ls)[(32)+1]<<8)|((lo)(ls)[(32)+2]<<16)|((lo)(ls)[(32)+3]<<24);};{(ld[
9])=((lo)(ls)[(36)])|((lo)(ls)[(36)+1]<<8)|((lo)(ls)[(36)+2]<<16)|((
lo)(ls)[(36)+3]<<24);};{(ld[10])=((lo)(ls)[(40)])|((lo)(ls)[(40)+1]<<
8)|((lo)(ls)[(40)+2]<<16)|((lo)(ls)[(40)+3]<<24);};{(ld[11])=((lo)(ls
)[(44)])|((lo)(ls)[(44)+1]<<8)|((lo)(ls)[(44)+2]<<16)|((lo)(ls)[(44)+
3]<<24);};{(ld[12])=((lo)(ls)[(48)])|((lo)(ls)[(48)+1]<<8)|((lo)(ls)[
(48)+2]<<16)|((lo)(ls)[(48)+3]<<24);};{(ld[13])=((lo)(ls)[(52)])|((lo
)(ls)[(52)+1]<<8)|((lo)(ls)[(52)+2]<<16)|((lo)(ls)[(52)+3]<<24);};{(
ld[14])=((lo)(ls)[(56)])|((lo)(ls)[(56)+1]<<8)|((lo)(ls)[(56)+2]<<16)|
((lo)(ls)[(56)+3]<<24);};{(ld[15])=((lo)(ls)[(60)])|((lo)(ls)[(60)+1]
<<8)|((lo)(ls)[(60)+2]<<16)|((lo)(ls)[(60)+3]<<24);};lk=lz->l23[0];li
=lz->l23[1];lg=lz->l23[2];lj=lz->l23[3];{lk+=(lj^(li&(lg^lj)))+ld[0]+
0xD76AA478;lk=((lk<<7)|((lk&0xFFFFFFFF)>>(32-7)))+li;};{lj+=(lg^(lk&(
li^lg)))+ld[1]+0xE8C7B756;lj=((lj<<12)|((lj&0xFFFFFFFF)>>(32-12)))+lk
;};{lg+=(li^(lj&(lk^li)))+ld[2]+0x242070DB;lg=((lg<<17)|((lg&
0xFFFFFFFF)>>(32-17)))+lj;};{li+=(lk^(lg&(lj^lk)))+ld[3]+0xC1BDCEEE;
li=((li<<22)|((li&0xFFFFFFFF)>>(32-22)))+lg;};{lk+=(lj^(li&(lg^lj)))+
ld[4]+0xF57C0FAF;lk=((lk<<7)|((lk&0xFFFFFFFF)>>(32-7)))+li;};{lj+=(lg
^(lk&(li^lg)))+ld[5]+0x4787C62A;lj=((lj<<12)|((lj&0xFFFFFFFF)>>(32-12
)))+lk;};{lg+=(li^(lj&(lk^li)))+ld[6]+0xA8304613;lg=((lg<<17)|((lg&
0xFFFFFFFF)>>(32-17)))+lj;};{li+=(lk^(lg&(lj^lk)))+ld[7]+0xFD469501;
li=((li<<22)|((li&0xFFFFFFFF)>>(32-22)))+lg;};{lk+=(lj^(li&(lg^lj)))+
ld[8]+0x698098D8;lk=((lk<<7)|((lk&0xFFFFFFFF)>>(32-7)))+li;};{lj+=(lg
^(lk&(li^lg)))+ld[9]+0x8B44F7AF;lj=((lj<<12)|((lj&0xFFFFFFFF)>>(32-12
)))+lk;};{lg+=(li^(lj&(lk^li)))+ld[10]+0xFFFF5BB1;lg=((lg<<17)|((lg&
0xFFFFFFFF)>>(32-17)))+lj;};{li+=(lk^(lg&(lj^lk)))+ld[11]+0x895CD7BE;
li=((li<<22)|((li&0xFFFFFFFF)>>(32-22)))+lg;};{lk+=(lj^(li&(lg^lj)))+
ld[12]+0x6B901122;lk=((lk<<7)|((lk&0xFFFFFFFF)>>(32-7)))+li;};{lj+=(
lg^(lk&(li^lg)))+ld[13]+0xFD987193;lj=((lj<<12)|((lj&0xFFFFFFFF)>>(32
-12)))+lk;};{lg+=(li^(lj&(lk^li)))+ld[14]+0xA679438E;lg=((lg<<17)|((
lg&0xFFFFFFFF)>>(32-17)))+lj;};{li+=(lk^(lg&(lj^lk)))+ld[15]+
0x49B40821;li=((li<<22)|((li&0xFFFFFFFF)>>(32-22)))+lg;};{lk+=(lg^(lj
&(li^lg)))+ld[1]+0xF61E2562;lk=((lk<<5)|((lk&0xFFFFFFFF)>>(32-5)))+li
;};{lj+=(li^(lg&(lk^li)))+ld[6]+0xC040B340;lj=((lj<<9)|((lj&
0xFFFFFFFF)>>(32-9)))+lk;};{lg+=(lk^(li&(lj^lk)))+ld[11]+0x265E5A51;
lg=((lg<<14)|((lg&0xFFFFFFFF)>>(32-14)))+lj;};{li+=(lj^(lk&(lg^lj)))+
ld[0]+0xE9B6C7AA;li=((li<<20)|((li&0xFFFFFFFF)>>(32-20)))+lg;};{lk+=(
lg^(lj&(li^lg)))+ld[5]+0xD62F105D;lk=((lk<<5)|((lk&0xFFFFFFFF)>>(32-5
)))+li;};{lj+=(li^(lg&(lk^li)))+ld[10]+0x02441453;lj=((lj<<9)|((lj&
0xFFFFFFFF)>>(32-9)))+lk;};{lg+=(lk^(li&(lj^lk)))+ld[15]+0xD8A1E681;
lg=((lg<<14)|((lg&0xFFFFFFFF)>>(32-14)))+lj;};{li+=(lj^(lk&(lg^lj)))+
ld[4]+0xE7D3FBC8;li=((li<<20)|((li&0xFFFFFFFF)>>(32-20)))+lg;};{lk+=(
lg^(lj&(li^lg)))+ld[9]+0x21E1CDE6;lk=((lk<<5)|((lk&0xFFFFFFFF)>>(32-5
)))+li;};{lj+=(li^(lg&(lk^li)))+ld[14]+0xC33707D6;lj=((lj<<9)|((lj&
0xFFFFFFFF)>>(32-9)))+lk;};{lg+=(lk^(li&(lj^lk)))+ld[3]+0xF4D50D87;lg
=((lg<<14)|((lg&0xFFFFFFFF)>>(32-14)))+lj;};{li+=(lj^(lk&(lg^lj)))+ld
[8]+0x455A14ED;li=((li<<20)|((li&0xFFFFFFFF)>>(32-20)))+lg;};{lk+=(lg
^(lj&(li^lg)))+ld[13]+0xA9E3E905;lk=((lk<<5)|((lk&0xFFFFFFFF)>>(32-5)))+
li;};{lj+=(li^(lg&(lk^li)))+ld[2]+0xFCEFA3F8;lj=((lj<<9)|((lj&
0xFFFFFFFF)>>(32-9)))+lk;};{lg+=(lk^(li&(lj^lk)))+ld[7]+0x676F02D9;lg
=((lg<<14)|((lg&0xFFFFFFFF)>>(32-14)))+lj;};{li+=(lj^(lk&(lg^lj)))+ld
[12]+0x8D2A4C8A;li=((li<<20)|((li&0xFFFFFFFF)>>(32-20)))+lg;};{lk+=(
li^lg^lj)+ld[5]+0xFFFA3942;lk=((lk<<4)|((lk&0xFFFFFFFF)>>(32-4)))+li;
};{lj+=(lk^li^lg)+ld[8]+0x8771F681;lj=((lj<<11)|((lj&0xFFFFFFFF)>>(32
-11)))+lk;};{lg+=(lj^lk^li)+ld[11]+0x6D9D6122;lg=((lg<<16)|((lg&
0xFFFFFFFF)>>(32-16)))+lj;};{li+=(lg^lj^lk)+ld[14]+0xFDE5380C;li=((li
<<23)|((li&0xFFFFFFFF)>>(32-23)))+lg;};{lk+=(li^lg^lj)+ld[1]+
0xA4BEEA44;lk=((lk<<4)|((lk&0xFFFFFFFF)>>(32-4)))+li;};{lj+=(lk^li^lg
)+ld[4]+0x4BDECFA9;lj=((lj<<11)|((lj&0xFFFFFFFF)>>(32-11)))+lk;};{lg
+=(lj^lk^li)+ld[7]+0xF6BB4B60;lg=((lg<<16)|((lg&0xFFFFFFFF)>>(32-16)))+
lj;};{li+=(lg^lj^lk)+ld[10]+0xBEBFBC70;li=((li<<23)|((li&0xFFFFFFFF)>>
(32-23)))+lg;};{lk+=(li^lg^lj)+ld[13]+0x289B7EC6;lk=((lk<<4)|((lk&
0xFFFFFFFF)>>(32-4)))+li;};{lj+=(lk^li^lg)+ld[0]+0xEAA127FA;lj=((lj<<
11)|((lj&0xFFFFFFFF)>>(32-11)))+lk;};{lg+=(lj^lk^li)+ld[3]+0xD4EF3085
;lg=((lg<<16)|((lg&0xFFFFFFFF)>>(32-16)))+lj;};{li+=(lg^lj^lk)+ld[6]+
0x04881D05;li=((li<<23)|((li&0xFFFFFFFF)>>(32-23)))+lg;};{lk+=(li^lg^
lj)+ld[9]+0xD9D4D039;lk=((lk<<4)|((lk&0xFFFFFFFF)>>(32-4)))+li;};{lj
+=(lk^li^lg)+ld[12]+0xE6DB99E5;lj=((lj<<11)|((lj&0xFFFFFFFF)>>(32-11)))+
lk;};{lg+=(lj^lk^li)+ld[15]+0x1FA27CF8;lg=((lg<<16)|((lg&0xFFFFFFFF)>>
(32-16)))+lj;};{li+=(lg^lj^lk)+ld[2]+0xC4AC5665;li=((li<<23)|((li&
0xFFFFFFFF)>>(32-23)))+lg;};{lk+=(lg^(li|~lj))+ld[0]+0xF4292244;lk=((
lk<<6)|((lk&0xFFFFFFFF)>>(32-6)))+li;};{lj+=(li^(lk|~lg))+ld[7]+
0x432AFF97;lj=((lj<<10)|((lj&0xFFFFFFFF)>>(32-10)))+lk;};{lg+=(lk^(lj
|~li))+ld[14]+0xAB9423A7;lg=((lg<<15)|((lg&0xFFFFFFFF)>>(32-15)))+lj;
};{li+=(lj^(lg|~lk))+ld[5]+0xFC93A039;li=((li<<21)|((li&0xFFFFFFFF)>>
(32-21)))+lg;};{lk+=(lg^(li|~lj))+ld[12]+0x655B59C3;lk=((lk<<6)|((lk&
0xFFFFFFFF)>>(32-6)))+li;};{lj+=(li^(lk|~lg))+ld[3]+0x8F0CCC92;lj=((
lj<<10)|((lj&0xFFFFFFFF)>>(32-10)))+lk;};{lg+=(lk^(lj|~li))+ld[10]+
0xFFEFF47D;lg=((lg<<15)|((lg&0xFFFFFFFF)>>(32-15)))+lj;};{li+=(lj^(lg
|~lk))+ld[1]+0x85845DD1;li=((li<<21)|((li&0xFFFFFFFF)>>(32-21)))+lg;}
;{lk+=(lg^(li|~lj))+ld[8]+0x6FA87E4F;lk=((lk<<6)|((lk&0xFFFFFFFF)>>(
32-6)))+li;};{lj+=(li^(lk|~lg))+ld[15]+0xFE2CE6E0;lj=((lj<<10)|((lj&
0xFFFFFFFF)>>(32-10)))+lk;};{lg+=(lk^(lj|~li))+ld[6]+0xA3014314;lg=((
lg<<15)|((lg&0xFFFFFFFF)>>(32-15)))+lj;};{li+=(lj^(lg|~lk))+ld[13]+
0x4E0811A1;li=((li<<21)|((li&0xFFFFFFFF)>>(32-21)))+lg;};{lk+=(lg^(li
|~lj))+ld[4]+0xF7537E82;lk=((lk<<6)|((lk&0xFFFFFFFF)>>(32-6)))+li;};{
lj+=(li^(lk|~lg))+ld[11]+0xBD3AF235;lj=((lj<<10)|((lj&0xFFFFFFFF)>>(
32-10)))+lk;};{lg+=(lk^(lj|~li))+ld[2]+0x2AD7D2BB;lg=((lg<<15)|((lg&
0xFFFFFFFF)>>(32-15)))+lj;};{li+=(lj^(lg|~lk))+ld[9]+0xEB86D391;li=((
li<<21)|((li&0xFFFFFFFF)>>(32-21)))+lg;};lz->l23[0]+=lk;lz->l23[1]+=
li;lz->l23[2]+=lg;lz->l23[3]+=lj;}lr l41(le l115*lz,lv lb*l13,lo l54){
lo l154,l175;lc(!l54)lh;l154=lz->l82[0]&0x3F;l175=64-l154;lz->l82[0]
+=l54;lz->l82[0]&=0xFFFFFFFF;lc(lz->l82[0]<l54)lz->l82[1]++;lc(l154&&
l54>=l175){l29((lr* )(lz->l263+l154),(lr* )l13,l175);l316(lz,lz->l263
);l54-=l175;l13+=l175;l154=0;}l72(l54>=64){l316(lz,l13);l54-=64;l13+=
64;}lc(l54)l29((lr* )(lz->l263+l154),(lr* )l13,l54);}l16 lb l404[64]=
{0x80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};lr
l144(lb l57[16],le l115*lz){lo l212,l322;lo l180,l194;lb l106[8];l180
=(lz->l82[0]>>29)|(lz->l82[1]<<3);l194=(lz->l82[0]<<3);{(l106)[(0)]=(
lb)((l194));(l106)[(0)+1]=(lb)((l194)>>8);(l106)[(0)+2]=(lb)((l194)>>
16);(l106)[(0)+3]=(lb)((l194)>>24);};{(l106)[(4)]=(lb)((l180));(l106)[
(4)+1]=(lb)((l180)>>8);(l106)[(4)+2]=(lb)((l180)>>16);(l106)[(4)+3]=(
lb)((l180)>>24);};l212=lz->l82[0]&0x3F;l322=(l212<56)?(56-l212):(120-
l212);l41(lz,l404,l322);l41(lz,l106,8);{(l57)[(0)]=(lb)((lz->l23[0]));
(l57)[(0)+1]=(lb)((lz->l23[0])>>8);(l57)[(0)+2]=(lb)((lz->l23[0])>>16
);(l57)[(0)+3]=(lb)((lz->l23[0])>>24);};{(l57)[(4)]=(lb)((lz->l23[1]));
(l57)[(4)+1]=(lb)((lz->l23[1])>>8);(l57)[(4)+2]=(lb)((lz->l23[1])>>16
);(l57)[(4)+3]=(lb)((lz->l23[1])>>24);};{(l57)[(8)]=(lb)((lz->l23[2]));
(l57)[(8)+1]=(lb)((lz->l23[2])>>8);(l57)[(8)+2]=(lb)((lz->l23[2])>>16
);(l57)[(8)+3]=(lb)((lz->l23[2])>>24);};{(l57)[(12)]=(lb)((lz->l23[3]
));(l57)[(12)+1]=(lb)((lz->l23[3])>>8);(l57)[(12)+2]=(lb)((lz->l23[3]
)>>16);(l57)[(12)+3]=(lb)((lz->l23[3])>>24);};}lb*l333(lv l8*l114,lv
l8*l299){lv l8*l117, *l167;l16 lb l95[16];l232 l11 ll,l224,l99;le l115
lz,l74;l11 l184;l99=l219(l114);l117=l299;lc(l527(l117,"\x24\x31\x24",
3)==0)l117+=3;l33(l167=l117; *l167!='\0'&& *l167!='$'&&l167<(l117+8);
l167++)l507;l224=l167-l117;l141(&lz);l41(&lz,(lv lb* )l114,l99);l41(&
lz,(lv lb* )"\x24\x31\x24",3);l41(&lz,(lv lb* )l117,l224);l141(&l74);
l41(&l74,(lv lb* )l114,l99);l41(&l74,(lv lb* )l117,l224);l41(&l74,(lv
lb* )l114,l99);l144(l95,&l74);l33(l184=l99;l184>0;l184-=16)l41(&lz,
l95,(l232 l11)(l184>16?16:l184));l401(l95,0,l81(l95));l33(ll=l99;ll!=
0;ll>>=1)lc((ll&1)!=0)l41(&lz,l95,1);ly l41(&lz,(lv lb* )l114,1);l144
(l95,&lz);l33(ll=0;ll<1000;ll++){l141(&l74);lc((ll&1)!=0)l41(&l74,(lv
lb* )l114,l99);ly l41(&l74,l95,16);lc((ll%3)!=0)l41(&l74,(lv lb* )l117
,l224);lc((ll%7)!=0)l41(&l74,(lv lb* )l114,l99);lc((ll&1)!=0)l41(&l74
,l95,16);ly l41(&l74,(lv lb* )l114,l99);l144(l95,&l74);}lh l95;}



#ifdef CRYPTO_ON
#define l24( l108, l254) (( lo)(( l108) + ( l254)))
#define l200( l108) ( l24(( l108),1))
le l110{lo l13[16];};lr l217(lb l169[64],lv lo l13[16]);lr l408(le
l110*ld,lv lb*l223,lb*lg,lo l88);lr l338(le l110*ld,lv lb*l71);lr l339
(le l110*ld,lv lb*l267);
#endif
#ifdef CRYPTO_ON
#define l28( l108, lg) ( ROTL32( l108, lg))
#define l27( l108, l254) (( l108) ^ ( l254))
#define l347( l61, l108) ((( lo  *  )( l61))[0] = l108)
#define l67( l61) ((( lo  *  )( l61))[0])
lr l217(lb l169[64],lv lo l13[16]){lo ld[16];l11 ll;l33(ll=0;ll<16;++
ll)ld[ll]=l13[ll];l33(ll=20;ll>0;ll-=2){ld[4]=l27(ld[4],l28(l24(ld[0]
,ld[12]),7));ld[8]=l27(ld[8],l28(l24(ld[4],ld[0]),9));ld[12]=l27(ld[
12],l28(l24(ld[8],ld[4]),13));ld[0]=l27(ld[0],l28(l24(ld[12],ld[8]),
18));ld[9]=l27(ld[9],l28(l24(ld[5],ld[1]),7));ld[13]=l27(ld[13],l28(
l24(ld[9],ld[5]),9));ld[1]=l27(ld[1],l28(l24(ld[13],ld[9]),13));ld[5]
=l27(ld[5],l28(l24(ld[1],ld[13]),18));ld[14]=l27(ld[14],l28(l24(ld[10
],ld[6]),7));ld[2]=l27(ld[2],l28(l24(ld[14],ld[10]),9));ld[6]=l27(ld[
6],l28(l24(ld[2],ld[14]),13));ld[10]=l27(ld[10],l28(l24(ld[6],ld[2]),
18));ld[3]=l27(ld[3],l28(l24(ld[15],ld[11]),7));ld[7]=l27(ld[7],l28(
l24(ld[3],ld[15]),9));ld[11]=l27(ld[11],l28(l24(ld[7],ld[3]),13));ld[
15]=l27(ld[15],l28(l24(ld[11],ld[7]),18));ld[1]=l27(ld[1],l28(l24(ld[
0],ld[3]),7));ld[2]=l27(ld[2],l28(l24(ld[1],ld[0]),9));ld[3]=l27(ld[3
],l28(l24(ld[2],ld[1]),13));ld[0]=l27(ld[0],l28(l24(ld[3],ld[2]),18));
ld[6]=l27(ld[6],l28(l24(ld[5],ld[4]),7));ld[7]=l27(ld[7],l28(l24(ld[6
],ld[5]),9));ld[4]=l27(ld[4],l28(l24(ld[7],ld[6]),13));ld[5]=l27(ld[5
],l28(l24(ld[4],ld[7]),18));ld[11]=l27(ld[11],l28(l24(ld[10],ld[9]),7
));ld[8]=l27(ld[8],l28(l24(ld[11],ld[10]),9));ld[9]=l27(ld[9],l28(l24
(ld[8],ld[11]),13));ld[10]=l27(ld[10],l28(l24(ld[9],ld[8]),18));ld[12
]=l27(ld[12],l28(l24(ld[15],ld[14]),7));ld[13]=l27(ld[13],l28(l24(ld[
12],ld[15]),9));ld[14]=l27(ld[14],l28(l24(ld[13],ld[12]),13));ld[15]=
l27(ld[15],l28(l24(ld[14],ld[13]),18));}l33(ll=0;ll<16;++ll)ld[ll]=
l24(ld[ll],l13[ll]);l33(ll=0;ll<16;++ll)l347(l169+4*ll,ld[ll]);}l16 lv
l8*l222="\x65\x78\x70\x61\x6e\x64\x20\x33\x32\x2d\x62\x79\x74\x65\x20"
"\x6b";lr l338(le l110*ld,lv lb*l71){ld->l13[1]=l67(l71+0);ld->l13[2]
=l67(l71+4);ld->l13[3]=l67(l71+8);ld->l13[4]=l67(l71+12);ld->l13[11]=
l67(l71+16);ld->l13[12]=l67(l71+20);ld->l13[13]=l67(l71+24);ld->l13[
14]=l67(l71+28);ld->l13[0]=l67(l222+0);ld->l13[5]=l67(l222+4);ld->l13
[10]=l67(l222+8);ld->l13[15]=l67(l222+12);}lr l339(le l110*ld,lv lb*
l267){ld->l13[6]=l67(l267+0);ld->l13[7]=l67(l267+4);ld->l13[8]=0;ld->
l13[9]=0;}lr l408(le l110*ld,lv lb*l223,lb*lg,lo l88){lb l169[64];
l232 l11 ll;lc(!l88)lh;l33(;;){l217(l169,ld->l13);ld->l13[8]=l200(ld
->l13[8]);lc(!ld->l13[8]){ld->l13[9]=l200(ld->l13[9]);}lc(l88<=64){
l33(ll=0;ll<l88;++ll)lg[ll]=l223[ll]^l169[ll];lh;}l33(ll=0;ll<64;++ll
)lg[ll]=l223[ll]^l169[ll];l88-=64;lg+=64;l223+=64;}}
#endif
#ifdef CRYPTO_ON
le l68{lb l44[64];lo l39;lb l73;le l110 l76;};lr l385(le l68*l22,le
l110*l340);lr l214(le l68*l22,lv lb*l123);lr l226(le l68*l22,lv lb*
l303);lr l124(le l68*l22,lv lb*l146,lb*l80,lo l14);
#else
le l68{lo l39;};
#endif
lo l121(lb*l138,lo l331,lo l83);
#ifdef CRYPTO_ON
lr l385(le l68*l22,le l110*l340){l22->l76= *l340;l22->l73=0;l22->l39=
0;}lr l214(le l68*l22,lv lb*l123){l338(&l22->l76,l123);}lr l226(le l68
 *l22,lv lb*l303){l339(&l22->l76,l303);l22->l73=0;l22->l39=0;}lr l124
(le l68*l22,lv lb*l146,lb*l80,lo l14){l232 l11 ll;lc(l22->l73){lb*ls=
l22->l44+64-l22->l73;lc(l14>=l22->l73){l14-=l22->l73;l33(ll=0;ll<l22
->l73;++ll)l80[ll]=l146[ll]^ls[ll];l146+=l22->l73;l80+=l22->l73;l22->
l73=0;}ly{l22->l73-=l14;l33(ll=0;ll<l14;++ll)l80[ll]=l146[ll]^ls[ll];
l14=0;}}lc(!l14)lh;l33(;;){l217((lb* )l22->l44,l22->l76.l13);l22->l76
.l13[8]=l200(l22->l76.l13[8]);lc(!l22->l76.l13[8])l22->l76.l13[9]=
l200(l22->l76.l13[9]);lc(l14<=64){l33(ll=0;ll<l14;++ll)l80[ll]=l146[
ll]^l22->l44[ll];l22->l73=64-l14;lh;}l33(ll=0;ll<64;++ll)l80[ll]=l146
[ll]^l22->l44[ll];l14-=64;l146+=64;l80+=64;}}
#endif
l16
#ifdef ARDUINO
__flash
#endif
lv lo l273[256]={0x00000000,0x77073096,0xee0e612c,0x990951ba,
0x076dc419,0x706af48f,0xe963a535,0x9e6495a3,0x0edb8832,0x79dcb8a4,
0xe0d5e91e,0x97d2d988,0x09b64c2b,0x7eb17cbd,0xe7b82d07,0x90bf1d91,
0x1db71064,0x6ab020f2,0xf3b97148,0x84be41de,0x1adad47d,0x6ddde4eb,
0xf4d4b551,0x83d385c7,0x136c9856,0x646ba8c0,0xfd62f97a,0x8a65c9ec,
0x14015c4f,0x63066cd9,0xfa0f3d63,0x8d080df5,0x3b6e20c8,0x4c69105e,
0xd56041e4,0xa2677172,0x3c03e4d1,0x4b04d447,0xd20d85fd,0xa50ab56b,
0x35b5a8fa,0x42b2986c,0xdbbbc9d6,0xacbcf940,0x32d86ce3,0x45df5c75,
0xdcd60dcf,0xabd13d59,0x26d930ac,0x51de003a,0xc8d75180,0xbfd06116,
0x21b4f4b5,0x56b3c423,0xcfba9599,0xb8bda50f,0x2802b89e,0x5f058808,
0xc60cd9b2,0xb10be924,0x2f6f7c87,0x58684c11,0xc1611dab,0xb6662d3d,
0x76dc4190,0x01db7106,0x98d220bc,0xefd5102a,0x71b18589,0x06b6b51f,
0x9fbfe4a5,0xe8b8d433,0x7807c9a2,0x0f00f934,0x9609a88e,0xe10e9818,
0x7f6a0dbb,0x086d3d2d,0x91646c97,0xe6635c01,0x6b6b51f4,0x1c6c6162,
0x856530d8,0xf262004e,0x6c0695ed,0x1b01a57b,0x8208f4c1,0xf50fc457,
0x65b0d9c6,0x12b7e950,0x8bbeb8ea,0xfcb9887c,0x62dd1ddf,0x15da2d49,
0x8cd37cf3,0xfbd44c65,0x4db26158,0x3ab551ce,0xa3bc0074,0xd4bb30e2,
0x4adfa541,0x3dd895d7,0xa4d1c46d,0xd3d6f4fb,0x4369e96a,0x346ed9fc,
0xad678846,0xda60b8d0,0x44042d73,0x33031de5,0xaa0a4c5f,0xdd0d7cc9,
0x5005713c,0x270241aa,0xbe0b1010,0xc90c2086,0x5768b525,0x206f85b3,
0xb966d409,0xce61e49f,0x5edef90e,0x29d9c998,0xb0d09822,0xc7d7a8b4,
0x59b33d17,0x2eb40d81,0xb7bd5c3b,0xc0ba6cad,0xedb88320,0x9abfb3b6,
0x03b6e20c,0x74b1d29a,0xead54739,0x9dd277af,0x04db2615,0x73dc1683,
0xe3630b12,0x94643b84,0x0d6d6a3e,0x7a6a5aa8,0xe40ecf0b,0x9309ff9d,
0x0a00ae27,0x7d079eb1,0xf00f9344,0x8708a3d2,0x1e01f268,0x6906c2fe,
0xf762575d,0x806567cb,0x196c3671,0x6e6b06e7,0xfed41b76,0x89d32be0,
0x10da7a5a,0x67dd4acc,0xf9b9df6f,0x8ebeeff9,0x17b7be43,0x60b08ed5,
0xd6d6a3e8,0xa1d1937e,0x38d8c2c4,0x4fdff252,0xd1bb67f1,0xa6bc5767,
0x3fb506dd,0x48b2364b,0xd80d2bda,0xaf0a1b4c,0x36034af6,0x41047a60,
0xdf60efc3,0xa867df55,0x316e8eef,0x4669be79,0xcb61b38c,0xbc66831a,
0x256fd2a0,0x5268e236,0xcc0c7795,0xbb0b4703,0x220216b9,0x5505262f,
0xc5ba3bbe,0xb2bd0b28,0x2bb45a92,0x5cb36a04,0xc2d7ffa7,0xb5d0cf31,
0x2cd99e8b,0x5bdeae1d,0x9b64c2b0,0xec63f226,0x756aa39c,0x026d930a,
0x9c0906a9,0xeb0e363f,0x72076785,0x05005713,0x95bf4a82,0xe2b87a14,
0x7bb12bae,0x0cb61b38,0x92d28e9b,0xe5d5be0d,0x7cdcefb7,0x0bdbdf21,
0x86d3d2d4,0xf1d4e242,0x68ddb3f8,0x1fda836e,0x81be16cd,0xf6b9265b,
0x6fb077e1,0x18b74777,0x88085ae6,0xff0f6a70,0x66063bca,0x11010b5c,
0x8f659eff,0xf862ae69,0x616bffd3,0x166ccf45,0xa00ae278,0xd70dd2ee,
0x4e048354,0x3903b3c2,0xa7672661,0xd06016f7,0x4969474d,0x3e6e77db,
0xaed16a4a,0xd9d65adc,0x40df0b66,0x37d83bf0,0xa9bcae53,0xdebb9ec5,
0x47b2cf7f,0x30b5ffe9,0xbdbdf21c,0xcabac28a,0x53b39330,0x24b4a3a6,
0xbad03605,0xcdd70693,0x54de5729,0x23d967bf,0xb3667a2e,0xc4614ab8,
0x5d681b02,0x2a6f2b94,0xb40bbe37,0xc30c8ea1,0x5a05df1b,0x2d02ef8d};lo
l121(lb*l138,lo l331,lo l83){l72(l331--)
#ifdef ARDUINO
#ifdef pgm_read_dword_far
l83=pgm_read_dword_far(l273+((l83^ *l138++)&0xff))^(l83>>8);
#else
l83=pgm_read_dword(l273+((l83^ *l138++)&0xff))^(l83>>8);
#endif
#else
l83=l273[(l83^ *l138++)&0xff]^(l83>>8);
#endif
lh l83^0xffffffff;}
lb*l333(lv l8*l114,lv l8*l299);l77 l321(lr);lo l260(lr);
#pragma pack(push, 1)
le l242{l111{le{lb l168;lb l44[15];}l0;l77 lp[2];}lm;};le l280{lb l44
[16];};le l381{l111{le{le l242 l59;le l280 l203;lb l253[8];lb l353[16
];lb l352[8];lb l376[4];}l0;l77 l325[8];lo l435[17];}lm;};l30 l530{
l487=0,l472=1,l465=2,l498=3};le l499{l12 l236:3;l12 l486:1;l12 l365:1
;l12 l536:3;l12 l475:7;l12 l512:1;};le l142{l12 l304;lo l382;lo l374;
lo l39;};le l229{lb l547;lb l137[32];l111{lo l122[4];
#ifdef WEBSOCKET
lb l365[80];
#endif
};lb l39;};
#pragma pack(pop)
le l85{le l68 l86;le l381 l34;};lr l311(le l85*l15,lv l8*l120,lv l8*
l282);l19 l336(le l85*l15,lo l211,lv lb*l123);l19 l323(le l85*l15,lv
lb*l218,lb*l80);lr l302(le l85*l15,le l142*l241);
#ifdef WEBSOCKET
lr l283(le l85*l15,lr*l314,l11 l14);
#endif
l77 l321(lr){l77 l26;l26=l327(); * ((lo* )(&l26)+1)=l327();lh l26;}lo
l260(lr){lo l26;l26=l327();lh l26;}l19 l543(lv lb*l120,lb l393,le l280
 *l123){lc(l393!=6)lh lq;lc(l539(l120,"\x76\x61\x6c\x65\x72\x61",6))lh
lq;l29(l123->l44,"\x50\x61\x73\x73\x77\x6f\x72\x64\x46\x6f\x72\x56"
"\x61\x6c\x65\x72",16);lh l2;}lr l361(le l242*l258,lv l8*l120){lb l152
[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};l11 l45=l219(l120);lc(l45>15)l45
=15;l258->lm.l0.l168=l45;l29(l258->lm.l0.l44,l120,l45);l29(l258->lm.
l0.l44+l45,l152,15-l45);}lr l311(le l85*l15,lv l8*l120,lv l8*l282){
l361(&l15->l34.lm.l0.l59,l120);l29(l15->l34.lm.l0.l203.l44,l333(l282,
l120),16);
#ifndef CRYPTO_ON
l15->l34.lm.l0.l59.lm.l0.l168|=0x80;
#endif
}l19 l336(le l85*l15,lo l211,lv lb*l123){lv l8*l320="\x79\x62\x6e\x64"
"\x72\x66\x67\x38\x65\x6a\x6b\x6d\x63\x70\x71\x78\x6f\x74\x31\x75\x77"
"\x69\x73\x7a\x61\x33\x34\x35\x68\x37\x36\x39";lb*l88=l15->l34.lm.l0.
l203.l44;l11 l31=0;l11 l189=3;l11 ll;l401(l88,0,16);l33(ll=0;ll<26;ll
++){l8*l61;lb li;lc(!l123[ll])lh lq;l61=l535((l8* )l320,l123[ll]);lc(
!l61)lh lq;li=l61-l320;lc(l189<0){l88[l31++]|=(lb)(li>>(-l189));lc(
l31==16)l10;l189+=8;}l88[l31]|=(lb)((li<<l189)&0xff);l189-=5;}l15->
l34.lm.l0.l59.lm.l0.l168=15;l15->l34.lm.l0.l59.lm.l0.l44[0]=0;l15->
l34.lm.l0.l59.lm.l0.l44[1]=l88[0];l15->l34.lm.l0.l59.lm.l0.l44[2]=l88
[1];l29(l15->l34.lm.l0.l59.lm.l0.l44+3,&l211,4);l15->l34.lm.l0.l59.lm
.lp[1]=0;
#ifndef CRYPTO_ON
l15->l34.lm.l0.l59.lm.l0.l168|=0x80;
#endif
lh l2;}lb l368(lo l17){lb l103= * ((lb* )&l17+0)%8;lb l62= * ((lb* )&
l17+1)%7;lb l58= * ((lb* )&l17+2)%6;lb l47= * ((lb* )&l17+3)%5;lc(l62
==l103)l62++;lc(l62>=8)l62-=8;l72(1){lc(l58==l103)l58++;ly{lc(l58==
l62)l58++;ly l10;}lc(l58>=8)l58-=8;}l72(1){lc(l47==l103)l47++;ly{lc(
l47==l62)l47++;ly{lc(l47==l58)l47++;ly l10;}}lc(l47>=8)l47-=8;}lh(1<<
l103)+(1<<l62)+(1<<l58)+(1<<l47);}l12 l405(lo l17){lb l103= * ((lb* )&
l17+0)%16;lb l62= * ((lb* )&l17+1)%15;lb l58= * ((lb* )&l17+2)%14;lb
l47= * ((lb* )&l17+3)%13;lc(l62==l103)l62++;lc(l62>=16)l62-=16;l72(1){
lc(l58==l103)l58++;ly{lc(l58==l62)l58++;ly l10;}lc(l58>=16)l58-=16;}
l72(1){lc(l47==l103)l47++;ly{lc(l47==l62)l47++;ly{lc(l47==l58)l47++;
ly l10;}}lc(l47>=16)l47-=16;}lh(1<<l103)+(1<<l62)+(1<<l58)+(1<<l47);}
l19 l323(le l85*l15,lv lb*l218,lb*l80){l77 l309;le l115 l94;l77 l271[
2];l111{l77 l319[2];lo l410[17];}lm;l19 l293=lq;l11 ll;l12 l251;lb*
l216;l11 l71;
#ifndef CRYPTO_ON
l15->l34.lm.l0.l59.lm.l0.l168&=0x7f;
#endif
l29(&l309,l218,8);l29(l15->l34.lm.l0.l253,l218+16,8);l33(ll=0;ll<256;
ll++){l19 l147;lb l256;lb*l204;lb*l202;lb*l201;lv lb*l227;l11 l268; *
((lb* )&l15->l34.lm.l0.l253)=ll;l141(&l94);l41(&l94,l15->l34.lm.l0.
l59.lm.l0.l44,l15->l34.lm.l0.l59.lm.l0.l168);l41(&l94,l15->l34.lm.l0.
l203.l44,16+8);l144((lb* )l271,&l94);l15->l34.lm.l325[5]=l309^l271[0]
;l141(&l94);l41(&l94,l15->l34.lm.l0.l253,8+8);l144((lb* )lm.l319,&l94
);l147=lq;l256=l368(lm.l410[0]);l204=(lb* )(l271+1);l202=l15->l34.lm.
l0.l353+8;l201=(lb* )(lm.l319+1);l227=l218+8;l33(l268=0;l268<8;l268++
){lc(l256&0x01) *l202= *l204^ *l227;ly{lc(( *l201^ *l204)== *l227) *
l202= *l201;ly{l147=l2;l10;}}l204++;l202++;l201++;l227++;l256>>=1;}lc
(!l147){l293=l2;l10;}}lc(!l293)lh lq;l15->l34.lm.l325[7]=l321();l29(
l80+16,l15->l34.lm.l0.l352,8);l141(&l94);l41(&l94,l15->l34.lm.l0.l203
.l44,16+8+16+8);l144(l80,&l94);l251=l405(l260());l15->l34.lm.l435[16]
=l260();l216=l15->l34.lm.l0.l376;l33(l71=0;l71<16;l71++){lc(l251&0x01
){lc( *l216==0) *l216=0xff;l80[l71]^= *l216++;}l251>>=1;}lh l2;}
#ifdef CRYPTO_ON
lr l302(le l85*l15,le l142*l241){l217((lb* )l15->l86.l76.l13,(lo* )&
l15->l34);l15->l86.l76.l13[8]=0;l15->l86.l76.l13[9]=0;l15->l86.l73=0;
l124(&l15->l86,(lb* )l241,(lb* )l241,l81(le l142));}lr l283(le l85*
l15,lr*l314,l11 l14){lb*lg=(lb* )l314;lb*l61=(lb* )l15->l86.l44+14;lb
 *l36=l61+50;l72(l14){l72(l14&&(l61<l36)){l14--; *lg= *lg^ *l61++;lg
++;}l61=(lb* )l15->l86.l44+47;}}
#endif
#if ( COUNT_SIGNALS > 255)
#error COUNT_SIGNALS should not be more than 255
#endif
#if ( RX_BUF_SIZE > 4096)
#error RX buffer size should not be more than 4096 bytes
#endif
#if ( TX_BUF_SIZE > 4096)
#error TX buffer size should not be more than 4096 bytes
#endif
#if ( RX_BUF_SIZE < 128)
#error RX buffer size must not be less than 128 bytes
#endif
#if ( TX_BUF_SIZE < 128)
#error TX buffer size must not be less than 128 bytes
#endif
#define l220 TX_BUF_SIZE - 22
l30 l502{l494=0,l462=1,l518=2,l549=3,l474=4,l511=5,l534=6,l456=7,l459
=100};l30 l192{l101=0,l513=1,l434=2,l490=3,l363=4,l497=5,l492=6,l469=
11,l506=12,l521=13,l449=21,l454=22,l413=23,l508=24,l476=25,l458=31,
l482=41,l542=42,l540=43,l451=44,l525=51,l455=52,l453=61,l532=71,l466=
100,l524=101,l545=102,l457=111,l431=112,l531=113};l30 l538{l505=0,
l544=1,l290=2,l357=3,l463=4,l516=5,l496=6};l30 l464{l416=0,l428=1,
l329=2,l377=3,l366=4,l235=5,l296=6,l285=7,l510=8,l324=9,l445=10,l379=
11,l478=12,l356=13,l384=14,l509=15,l328=20,l423=21,l295=100,l436=101,
l388=103,l437=104,l406=105,l371=106,l349=200,l358=250};l30 l301{l279=
0,l310=1,l294=2,l337=3,l335=4,l334=5,l326=6,l230=7,l198=8,l153=9,l173
=10,l520=11,l438=12};le l417{l111{le{lb l477:2;lb l375:1;lb l488:1;lb
l500:1;lb l442:1;lb l305:1;lb l485:1;}l0;lb lp;}lm;};l250 l206 l66;
l30 l433{l517=0x00,l187=0x10,l172=0x20,l261=0x30,l332=0x40};le l255{
lr*l135;l130( *l298)(lr*l313);l130( *l237)(lr*l313,lb*l138,l12 l14,
l19*l461);lr( *l281)(lr*l313);};le l185{l111{l206 l51:56;le{l77 l448:
56;l77 l145:8;}l0;}l37;l111{l19 l441;l419 l392;lb l156;l130 l420;l12
l346;l129 l415;lo l341;l312 l318;l195 l269;l8*l345;lb*l55;le l255*l64
;le{lb l181;lb l118;lb l213;}l53;}lw;};le l248{l12 l468:10;l12 l470:3
;l12 l411:3;};le l9{le l185 lp;lv l8*l159;l111{le{lb l56:5;lb l112:1;
lb l170:1;lb l157:1;}l20;le{lb l533:6;lb l149:2;}l133;}lm;le l417 l127
;};l16 l12 l196(le l9*ln){l148(ln->lm.l20.l56){l6 l279:l6 l310:l6 l294
:lh 1;l6 l337:l6 l335:lh 2;l6 l334:l6 l326:l6 l230:lh 4;l6 l198:lh l81
(l195);l6 l153:lc(!ln->lp.lw.l345)lh 0;lh(l12)l219(ln->lp.lw.l345);l6
l173:lc(!ln->lp.lw.l55)lh 0;lh ln->lp.lw.l55[0]+(ln->lp.lw.l55[1]<<8);
l225:lh 0;}}l16 l19 l330(le l9*ln,l206 l17,l66 l32){l148(ln->lm.l20.
l56){l6 l279:ln->lp.lw.l441=l17?l2:lq;l10;l6 l310:lc((-0x80>l17)||(
l17>0x7f))lh lq;ln->lp.lw.l392=(l419)l17;l10;l6 l294:lc((0>l17)||(l17
>0xff))lh lq;ln->lp.lw.l156=(lb)l17;l10;l6 l337:lc((-0x8000>l17)||(
l17>0x7fff))lh lq;ln->lp.lw.l420=(l130)l17;l10;l6 l335:lc((0>l17)||(
l17>0xffff))lh lq;ln->lp.lw.l346=(l12)l17;l10;l6 l334:lc((-
0x80000000LL>l17)||(l17>0x7fffffff))lh lq;ln->lp.lw.l415=(l129)l17;
l10;l6 l326:lc((0>l17)||(l17>0xffffffff))lh lq;ln->lp.lw.l341=(lo)l17
;l10;l6 l230:ln->lp.lw.l318=(l312)l17;l10;l6 l198:ln->lp.lw.l269=(
l195)l17;l10;l225:lh lq;}lc(l32!=LLONG_MIN)ln->lp.l37.l51=l32;lh l2;}
l16 l19 l378(le l9*ln,l195 l17,l66 l32){l148(ln->lm.l20.l56){l6 l230:
ln->lp.lw.l318=(l312)l17;l10;l6 l198:ln->lp.lw.l269=l17;l10;l225:lh
l330(ln,(l206)l17,l32);}lc(l32!=LLONG_MIN)ln->lp.l37.l51=l32;lh l2;}
l16 l19 l380(le l9*ln,lv lr*l244,l66 l32){lc(l32!=LLONG_MIN)ln->lp.
l37.l51=l32;ln->lp.lw.l55=(lb* )l244;lh l2;}l16 l19 l362(le l9*ln,l66
l32){ln->lp.l37.l51=l32;lh l2;}l30 l390{l396=0,l234=1,l240=2,l247=3,
l418=4,l409=5};l250 lr( *l421)(l30 l390 l541,le l9*ln,le l185*l522);
#ifdef ARDUINO
l250 lr( *l286)(lv __FlashStringHelper*l432,...);
#else
l250 lr( *l286)(lv l8*l432,...);
#endif
le l262{l19( *l238)(lv l8*l460,l12 l514);l11( *l383)(lr*l138,l12 l14);
l19( *l136)(lv lr*l138,l12 l14);lr( *l367)(lr);lr( *l292)(lr);l19( *
l191)(lr);l19( *l398)(lr);};le l163{lo l297;lv l8*l59;lv l8*l288;l421
l78;l286 l35;le l248*l221;l11 l400;};le l1{l111{le l85 l96;le{le l68
l100;lb l102[TX_BUF_SIZE];}l0;}lm;lb l5[RX_BUF_SIZE];l12 l63;l12 l50;
le l68 l87;lb l137[32];lo l122;l12 l128;lv l8*l266;le l163 l7;le l262
l42;lb l18;l66 l193;l66 l183;l66 l70;lb l48;lb l179;lb l164;l19 l134;
l19 l171;l19 l197;
#ifdef WEBSOCKET
lb l79;
#endif
lb l236;
#ifdef ATTACHED_MODE
lb l125;
#endif
le l9 l3[1];};l30 l424{l93=0,l91=1,l351=2,l60=3,l243=4,l177=5,l289,
l308,l300,l239,};l16 lr l444(lb*l395,l8*l98){lv l8*l155="\x30\x31\x32"
"\x33\x34\x35\x36\x37\x38\x39";l11 l31=0;l11 ll;l19 l246;l33(ll=0;ll<
4;ll++){lb l178=l395[ll];lb l132=l178%100;l98[l31]=l155[l178/100];
l246=lq;lc(l98[l31]=='0')l246=l2;ly l31++;l178=l132;l132=l178%10;l98[
l31]=l155[l178/10];lc((!l246||l98[l31]!='0'))l31++;l98[l31++]=l155[
l132];l98[l31++]='.';}l98[--l31]=0;}
#ifdef WEBSOCKET
l16 lr l364(lb*l207,l8*l245){lv l8*l155="\x30\x31\x32\x33\x34\x35\x36"
"\x37\x38\x39\x61\x62\x63\x64\x65\x66";l33(l11 ll=0;ll<8;ll++){lb l317
= *l207++;l245[1]=l155[l317&0x0f];l245[0]=l155[l317>>4];l245+=2;}}lb*
l354(lb*l207,l12 l14){l11 l23=0;lb*l140=l207;lb*l36=l207+l14;l72(l140
<l36){l148(l23){l6 0:lc( *l140=='\r')l23=1;l10;l6 1:lc( *l140!='\n')lh
0;l23=2;l10;l6 2:lc( *l140=='\r')l23=3;ly l23=0;l10;l6 3:lc( *l140!=
'\n')lh 0;lh l140+1;}l140++;}lh 0;}
#endif
l16 lr l278(le l1*la,l8*l98,lv l8* *l228){lc(la->l122==0) *l228=la->
l266;ly{l444((lb* )&la->l122,l98); *l228=l98;}}l16 lr l291(le l1*la){
#ifdef CRYPTO_ON
l77 l75[8];le l68*l176=&la->lm.l96.l86;lv l77 l152[8]={0,0,0,0,0,0,0,
0};l214(l176,(lb* )la->l137);l226(l176,(lb* )l152);l124(l176,(lb* )l152
,(lb* )l75,64);l29(la->l137+2,l75+4,30);l214(l176,(lb* )l75);l226(
l176,(lb* )l152);l75[4]=l75[1];l75[5]=l75[3];l75[6]=l75[0];l75[7]=l75
[2];l214(&la->l87,(lb* )(l75+4));l226(&la->l87,(lb* )l152);
#endif
la->lm.l96.l86.l39=0;la->l87.l39=0;}l16 lr l52(le l1*la,l12 l14,l19
l440){lc(!la->l197&&l440){la->l197=l2;la->l70=l107()+100;}la->l50+=
l14;}l16 lr l210(le l1*la,l19 l348){lc(!l348){lc(la->l42.l191())lh;}
#ifdef WEBSOCKET
l11 l160=la->l79?8:2;lc(la->l50>l160){l12 l38=la->l50-l160;la->l50+=4
;lb*lf=la->lm.l0.l102;lb*ls=lf+l160;lc(la->l79){l38+=4;lc(l38>125){lf
[0]=0x82;lf[1]=126|0x80;lf[2]= * ((lb* )&l38+1);lf[3]= * ((lb* )&l38+
0);lf[4]=0;lf[5]=0;lf[6]=0;lf[7]=0;}ly{lf+=2;lf[0]=0x82;lf[1]=l38|
0x80;lf[2]=0;lf[3]=0;lf[4]=0;lf[5]=0;la->l50-=2;}l38-=4;}ly{lf[0]= * (
(lb* )&l38+0);lf[1]= * ((lb* )&l38+1);}la->l87.l39=l121(ls,l38,la->
l87.l39);l29(ls+l38,&(la->l87.l39),4);lc(!la->l79){ls-=2;l38+=2;}l124
(&la->l87,ls,ls,l38+4);lc(!la->l42.l136(lf,la->l50))la->l7.l35(F(""
"\x45\x72\x72\x6f\x72\x20\x73\x65\x6e\x64\x69\x6e\x67\x20\x64\x61\x74"
"\x61\x21\n"));la->l50=la->l79?8:2;la->l197=lq;}
#else
lc(la->l50>2){l12 l38;l38=la->l50-2;la->lm.l0.l102[0]= * ((lb* )&l38+
0);la->lm.l0.l102[1]= * ((lb* )&l38+1);la->l87.l39=l121(la->lm.l0.
l102+2,l38,la->l87.l39);l29(la->lm.l0.l102+la->l50,&(la->l87.l39),4);
la->l50+=4;
#ifdef CRYPTO_ON
l124(&la->l87,la->lm.l0.l102,la->lm.l0.l102,la->l50);
#endif
lc(!la->l42.l136(la->lm.l0.l102,la->l50))la->l7.l35(F("\x45\x72\x72"
"\x6f\x72\x20\x73\x65\x6e\x64\x69\x6e\x67\x20\x64\x61\x74\x61\x21\n"));
la->l50=2;la->l197=lq;}
#endif
}l16 lb*l40(le l1*la,l12 l14){
#ifdef WEBSOCKET
l11 l264=0;l11 l160=0;lc(la->l79){l264=12;l160=8;}ly{l264=6;l160=2;}
lc(l14>((TX_BUF_SIZE-l264)-la->l50))l210(la,l2);
#else
lc(l14>((TX_BUF_SIZE-4)-la->l50))l210(la,l2);
#endif
lh la->lm.l0.l102+la->l50;}l16 l19 l182(le l1*la,l66 l270){lh((l66)(
l270&0xffffffffffff0000LL)!=la->l183);}l16 lr l174(le l1*la,l66 l270){
lb*lf;la->l183=l270&0xffffffffffff0000LL;lf=l40(la,8);lf[0]=0x86;lf[1
]=l329;l29(lf+2,(lb* )&la->l183+2,6);l52(la,8,lq);}l16 l19 l372(le l1
 *la,lb l105){lb*lf;l129 lu;le l9*lt=la->l3+l105;lc(lt->lm.l20.l56==
l438)lt->lp.lw.l341=0;lu=l219(lt->l159);lc(lu>64)lh lq;lf=l40(la,5+lu
);lf[0]=(lb)(0x83+lu);lf[1]=l324;lf[2]=l105;lf[3]=lt->lm.l20.l56;lf[4
]=lt->l127.lm.lp;l29(lf+5,lt->l159,lu);l52(la,lu+5,lq);lh l2;}
#ifdef ATTACHED_MODE
l16 l19 l439(le l1*la,lb l105,lo*l211){l129 l109;lv l8*l161=la->l3[
l105].l159;l8*l104=l359((l8* )l161,'@');lc(l104==0)lh lq;l109=l104-
l161;lc(l109>64)lh lq;l104+=1; *l211=l387(l104);lh l2;}l16 l19 l249(
le l1*la,lb l105){lb*lf;l129 l109;le l9*lt=la->l3+l105;lt->lm.l20.
l170=l2;lv l8*l161=lt->l159;l8*l104=l359((l8* )l161,'@');lc(l104==0)lh
lq;l109=l104-l161;lc(l109>64)lh lq;l104+=1;lo l113=l387(l104);lf=l40(
la,9+l109);lf[0]=0x87+l109;lf[1]=l285;lf[2]=l113;lf[3]=l113>>8;lf[4]=
l113>>16;lf[5]=l113>>24;lf[6]=0;lf[7]=0;lf[8]=l105;l29(lf+9,l161,l109
);l52(la,9+l109,l2);lh l2;}l16 lr l369(le l1*la){la->l48=la->l125;lc(
la->l18==l60){lb*lf;lf=l40(la,2);lf[0]=0x80;lf[1]=l445;l52(la,2,l2);}
}
#endif
l16 lr l373(le l1*la,le l248 l276,lb l105){lb*lf=l40(la,5);lf[0]=(lb)0x83
;lf[1]=l384;lf[2]= * ((lb* )&l276+0);lf[3]= * ((lb* )&l276+1);lf[4]=
l105;l52(la,5,lq);}l16 lr l233(le l1*la,le l9*ln,l30 l192 l65,l12 l14
,l19 l116){lb*lf;lc(l65==l101){l11 l31;l130 l45=4+l14;lc((l45<127)&&(
!l116)){lf=l40(la,6+l14);lf[0]=l45|0x80;l31=1;}ly{lf=l40(la,8+l14);lf
[0]=0xff;lf[1]=(lb)l45;lf[2]=(lb)(l45>>8);lc(l116)lf[2]|=l187;l31=3;}
lf[l31++]=l235;lf[l31++]=l101;lf[l31++]=ln-la->l3;lf[l31++]=(lb)ln->
lp.l37.l51;lf[l31++]= * ((lb* )&ln->lp+1);lc(!l116){lb*ls;lc(ln->lm.
l20.l56==l153)ls=ln->lp.lw.l55;ly lc(ln->lm.l20.l56==l173)ls=ln->lp.
lw.l55+2;ly ls=&ln->lp.lw.l156;l29(lf+l31,ls,l14);}l52(la,l31+l14,
l116?lq:l2);}ly{lf=l40(la,4);lf[0]=0x82;lf[1]=l235;lf[2]=l65;lf[3]=ln
-la->l3;l52(la,4,l2);}}l16 lr l274(le l1*la,le l9*ln,l12 l14,l19 l116
){lb*lf;l11 l31;l130 l45=3+l14;lc((l45<127)&&(!l116)){lf=l40(la,4+l14
);lf[0]=(lb)(0x03+l14);l31=1;}ly{lf=l40(la,6+l14);lf[0]=0x7f;lf[1]=(
lb)l45;lf[2]=(lb)(l45>>8);lc(l116)lf[2]|=l187;l31=3;}lf[l31++]=ln-la
->l3;lf[l31++]=(lb)ln->lp.l37.l51;lf[l31++]= * ((lb* )&ln->lp+1);lc(!
l116){lb*ls;lc(ln->lm.l20.l56==l153)ls=ln->lp.lw.l55;ly lc(ln->lm.l20
.l56==l173)ls=ln->lp.lw.l55+2;ly ls=&ln->lp.lw.l156;l29(lf+l31,ls,l14
);}l52(la,l31+l14,l116?lq:l2);}l16 l19 l208(le l1*la,le l9*ln,l30 l433
l89){l130 lu;lb*lf;l19 l151;l11 l25;l148(l89){l6 l172:{lu=ln->lp.lw.
l64->l298(ln->lp.lw.l64->l135);lc(lu==0){ln->lp.lw.l64->l237(ln->lp.
lw.l64->l135,0,0,&l151);lh l2;}lc(lu>0){lc(lu>l220)lu=l220;l25=(ln->
lm.l20.l157)?5:4;lf=l40(la,l25+lu);lu=ln->lp.lw.l64->l237(ln->lp.lw.
l64->l135,lf+l25,lu,&l151);lc((lu==0)&&(!l151))lh l2;}ly lf=l40(la,5);
lc(lu<0){lu=0;l89=l261;l10;}lc(l151)l89=l332;ly l89=l172;l10;}l6 l187
:{lu=ln->lp.lw.l64->l298(ln->lp.lw.l64->l135);lc(lu>=0){lc(l182(la,ln
->lp.l37.l51))l174(la,ln->lp.l37.l51);lc(lu>l220)lu=l220;l25=(ln->lm.
l20.l157)?8:6;lf=l40(la,l25+lu);lu=ln->lp.lw.l64->l237(ln->lp.lw.l64
->l135,lf+l25,lu,&l151);}lc(lu<0){lc(ln->lm.l20.l157)l233(la,ln,l434,
0,lq);ln->lm.l133.l149=0;lh lq;}ly{lc(ln->lm.l20.l157)l233(la,ln,l101
,lu,l2);ly l274(la,ln,lu,l2);lc(!l151)lh l2;lf=l40(la,5);lu=0;l89=
l332;}l10;}l6 l261:lf=l40(la,5);lu=0;l10;l225:lh lq;}lu++;lc(ln->lm.
l20.l170){lf[0]=0x7f;lf[1]=(lb)lu;lf[2]=l89+ * ((lb* )&lu+1);lf[3]=ln
-la->l3;l52(la,3+lu,(l89==l172)?lq:l2);}ly{lf[0]=0xff;lf[1]=(lb)lu;lf
[2]=l89+ * ((lb* )&lu+1);lf[3]=l235;lf[4]=ln-la->l3;l52(la,4+lu,(l89
==l172)?lq:l2);}lc(l89!=l172)ln->lm.l133.l149=0;lh l2;}l16 lr l344(le
l1*la,le l9*ln){lc((!ln->lm.l20.l112)&&(!la->l164)){lc((lb)ln->lp.l37
.l0.l145==255)lh;}lc(ln->l127.lm.l0.l305){lc(ln->lm.l133.l149){ln->lp
.lw.l64->l281(ln->lp.lw.l64->l135);l208(la,ln,l261);}ln->lm.l20.l170=
1;l208(la,ln,l187);lh;}lc(l182(la,ln->lp.l37.l51))l174(la,ln->lp.l37.
l51);l274(la,ln,l196(ln),lq);}l16 lr l284(le l1*la,le l9*l97,lv l8*
l139,l66 l32){lb l4;l129 lu;lb*lf;l4=l97-la->l3;lc(la->l3[l4].lp.lw.
l53.l213)lh;lc(la->l3[l4].lp.l37.l0.l145!=255){lb l150=la->l164;lc(
l150){l72(la->l3[l150].lp.lw.l53.l118)l150=la->l3[l150].lp.lw.l53.
l118;la->l3[l150].lp.lw.l53.l118=l4;}ly la->l164=l4;la->l3[l4].lp.lw.
l53.l181=l150;la->l3[l4].lp.lw.l53.l118=0;}la->l3[l4].lp.lw.l53.l213=
1;lc(l182(la,l32))l174(la,l32);lu=l219(l139)+3;lc(lu>127){lf=(lb* )l40
(la,4+lu);lf[0]=0xff;lf[1]= * ((lb* )(&lu)+0);lf[2]= * ((lb* )(&lu)+1
);lf[3]=l328;lf[4]=l4;lf[5]=(lb)l32;lf[6]= * ((lb* )&l32+1);l29(lf+7,
l139,lu-3);l52(la,4+lu,lq);}ly{lf=(lb* )l40(la,2+lu);lf[0]=0x80+lu;lf
[1]=l328;lf[2]=l4;lf[3]=(lb)l32;lf[4]= * ((lb* )&l32+1);l29(lf+5,l139
,lu-3);l52(la,2+lu,lq);}}l16 lr l342(le l1*la,le l9*l97){lb l4;lb*lf;
l4=l97-la->l3;lc(!la->l3[l4].lp.lw.l53.l213)lh;lc(la->l3[l4].lp.l37.
l0.l145!=255){lc(la->l3[l4].lp.lw.l53.l181)la->l3[la->l3[l4].lp.lw.
l53.l181].lp.lw.l53.l118=la->l3[l4].lp.lw.l53.l118;ly la->l164=la->l3
[l4].lp.lw.l53.l118;lc(la->l3[l4].lp.lw.l53.l118)la->l3[la->l3[l4].lp
.lw.l53.l118].lp.lw.l53.l181=la->l3[l4].lp.lw.l53.l181;}la->l3[l4].lp
.lw.l53.l213=0;lf=(lb* )l40(la,3);lf[0]=0x81;lf[1]=l423;lf[2]=l4;l52(
la,3,l2);}l16 lr l422(le l1*la,le l9*ln,l30 l192 l65){l12 lu;lc((ln->
l127.lm.l0.l305)&&(l65==l101)){lc(ln->lm.l133.l149)l65=l363;ly{ln->lm
.l20.l157=1;l208(la,ln,l187);lh;}}lu=0;lc(l65==l101){lc(l182(la,ln->
lp.l37.l51))l174(la,ln->lp.l37.l51);lu=l196(ln);}l233(la,ln,l65,lu,lq
);}l16 lr l446(le l1*la,le l9*ln,l30 l192 l65){lb*lf;lc(l65==l101){lc
(l182(la,ln->lp.l37.l51))l174(la,ln->lp.l37.l51);lf=l40(la,6);lf[0]=
0x84;lf[1]=l296;lf[2]=l101;lf[3]=ln-la->l3;lf[4]=(lb)ln->lp.l37.l51;
lf[5]=(lb)(ln->lp.l37.l51>>8);l52(la,6,l2);}ly{lf=l40(la,4);lf[0]=
0x82;lf[1]=l296;lf[2]=l65;lf[3]=ln-la->l3;l52(la,4,l2);}}l16 lr l443(
le l1*la,lb l430){lb*lf=l40(la,3);lf[0]=0x81;lf[1]=l379;lf[2]=l430;
l52(la,3,l2);}
#if ( RX_BUF_SIZE < 4096)
l16 lr l426(le l1*la,l12 l14){lb*lf=l40(la,4);lf[0]=0x82;lf[1]=l356;
lf[2]=(lb)l14;lf[3]=(lb)(l14>>8);l52(la,4,lq);}
#endif
l16 lr l407(le l1*la,le l163*l166,le l262*l272){la->l7= *l166;la->l42
= *l272;la->l48=1;
#ifdef ATTACHED_MODE
la->l125=1;
#endif
la->l179=0;la->l193=0;la->l18=l93;la->l63=0;la->l134=l2;la->l171=lq;
la->l164=0;la->l70=l107();}l16 le l9*l355(le l1*la,lv l8*l143,l30 l301
l186,lb l252,l12 l231,le l255*l199){le l9*lt=la->l3+la->l48++;l111{le
l248 l287;l12 l429;}lm;lm.l429=l231;lc((lb* )lt>=(lb* )la->l7.l221){
la->l7.l35(F("\x49\x6e\x63\x72\x65\x61\x73\x65\x20\x74\x68\x65\x20"
"\x76\x61\x6c\x75\x65\x20\x43\x4f\x55\x4e\x54\x5f\x53\x49\x47\x4e\x41"
"\x4c\x53\x20\x21\n"));l72(1);}
#ifdef ATTACHED_MODE
la->l125=la->l48;
#endif
lt->l159=l143;lc(l186==l198){lc(l81(l195)==4)l186=l230;}lt->lm.l20.
l56=l186;lt->lm.l20.l112=0;lt->lm.l20.l170=0;lt->lm.l20.l157=0;lt->
l127.lm.lp=l252;lt->lp.lw.l269=0;lc(l199)lt->lp.lw.l64=l199;lc(lm.
l287.l411){lc(la->l179>=la->l7.l400){la->l7.l35(F("\x49\x6e\x63\x72"
"\x65\x61\x73\x65\x20\x74\x68\x65\x20\x76\x61\x6c\x75\x65\x20\x43\x4f"
"\x55\x4e\x54\x5f\x53\x54\x4f\x52\x45\x20\x21\n"));l72(1);}lt->lp.l37
.l0.l145=la->l179;la->l7.l221[la->l179]=lm.l287;la->l179++;}ly lt->lp
.l37.l0.l145=255;lh lt;}
#ifdef ATTACHED_MODE
l16 le l9*l394(le l1*la,lv l8*l143){le l9*lt=la->l3+la->l48++;lc((lb*
)lt>=(lb* )la->l7.l221){la->l48--;la->l7.l35(F("\x49\x6e\x63\x72\x65"
"\x61\x73\x65\x20\x74\x68\x65\x20\x76\x61\x6c\x75\x65\x20\x43\x4f\x55"
"\x4e\x54\x5f\x53\x49\x47\x4e\x41\x4c\x53\x20\x21\n"));lh 0;}lt->l159
=l143;lc(la->l18==l60)l249(la,la->l48-1);lh lt;}
#endif
l16 l19 l399(le l1*la,l19*l350){l11 l49;lc(la->l18==l91){lc(la->l7.
l59)l311(&la->lm.l96,la->l7.l59,la->l7.l288);ly{lc(!l336(&la->lm.l96,
la->l7.l297,(lb* )la->l7.l288)){la->l7.l35(F("\x50\x61\x73\x73\x77"
"\x6f\x72\x64\x20\x69\x73\x20\x65\x72\x72\x6f\x72\x21\n"));la->l18=
l93;lh l2;}}la->l7.l35(F("\x57\x61\x69\x74\x20\x63\x6f\x6e\x6e\x65"
"\x63\x74\x69\x6f\x6e\x2e\x2e\x2e\n"));lc(!la->l42.l238(la->l266,4502
)){la->l7.l35(F("\x4e\x6f\x20\x63\x6f\x6e\x6e\x65\x63\x74\x69\x6f\x6e"
"\x20\x77\x69\x74\x68\x20\x74\x68\x65\x20\x73\x65\x72\x76\x69\x63\x65"
"\n"));la->l70=l107()+2000;lh lq;}la->l18=l289;}l49=la->l42.l383(la->
l5+la->l63,RX_BUF_SIZE-la->l63);lc(l49<0)lh lq;lc(la->l18==l289){lc(!
la->l42.l398())lh l2;la->l7.l35(F("\x57\x61\x69\x74\x20\x61\x75\x74"
"\x68\x6f\x72\x69\x7a\x61\x74\x69\x6f\x6e\x2e\x2e\x2e\n"));la->l42.
l136(&la->lm.l96.l34.lm.l0.l59,l81(le l242));la->l18=l308;}lc((l49==0
)&&(la->l134)){lh l2;} *l350=l2;l148(la->l18){l6 l308:{lb lf[24+l81(
le l142)];le l142 l126;lc(l49!=24)lh lq;lc(!l323(&la->lm.l96,la->l5,
lf))lh lq;
#ifdef WEBSOCKET
l126.l304=la->l236+(1<<4)+(1<<5);
#else
l126.l304=1;
#endif
l126.l382=la->l7.l297;l126.l374=0xffffffffL;l126.l39=l121((lb* )&l126
,offsetof(le l142,l39),0xffffffff);
#ifdef CRYPTO_ON
l302(&la->lm.l96,&l126);
#endif
l29(lf+24,&l126,l81(le l142));lc(!la->l42.l136(lf,l81(lf)))lh lq;la->
l42.l367();la->l18=l300;lh l2;}l6 l300:{lb l147;lv l8*l131;l8 l257[12
+3+1];
#ifdef WEBSOCKET
lc(l49<(offsetof(le l229,l122)+2))
#else
lc(l49!=l81(le l229))
#endif
lh lq;
#ifdef CRYPTO_ON
#ifdef WEBSOCKET
l283(&la->lm.l96,la->l5,l49);
#else
l124(&la->lm.l96.l86,la->l5,la->l5,l49);
#endif
#endif
#ifdef WEBSOCKET
lc(la->l5[l49-1]!=(lb)l121(la->l5,l49-1,0xffffffff))
#else
lc(la->l5[offsetof(le l229,l39)]!=(lb)l121(la->l5,offsetof(le l229,
l39),0xffffffff))
#endif
lh lq;l147=la->l5[0];la->l42.l292();lc(l147!=l101){l148(l147){l6 l431
:la->l7.l35(F("\x54\x68\x65\x20\x73\x65\x72\x76\x69\x63\x65\x20\x69"
"\x73\x20\x62\x72\x6f\x6b\x65\x6e\n"));l10;l6 l413:la->l70=l107()+
10000;la->l7.l35(F("\x54\x68\x65\x20\x64\x65\x76\x69\x63\x65\x20\x69"
"\x73\x20\x6e\x6f\x74\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64\n"));
l10;}lh lq;}lc(l49==50){la->l79=0;la->l122=la->l5[33]; * ((lb* )&la->
l122+1)=la->l5[34]; * ((lb* )&la->l122+2)=la->l5[35]; * ((lb* )&la->
l122+3)=la->l5[36]; * ((lb* )&la->l128+0)=la->l5[37]; * ((lb* )&la->
l128+1)=la->l5[38];lc(!la->l128)la->l128=4503;l278(la,l257,&l131);}ly
{la->l79=1;l131=(l8* )la->l5+33;la->l5[l49-1]=0;la->l128=80;}lc(!la->
l42.l238(l131,la->l128)){la->l7.l35(F("\x4c\x6f\x73\x73\x20\x6f\x66"
"\x20\x63\x6f\x6e\x6e\x65\x63\x74\x69\x6f\x6e\n"));la->l18=l91;lh l2;
}l29(la->l137,la->l5+1,32);l291(la);
#ifdef WEBSOCKET
lc(la->l79){l8 lf[38+80+91]="\x47\x45\x54\x20\x2f\x30\x30\x30\x30\x30"
"\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x20\x48\x54\x54\x50\x2f"
"\x31\x2e\x31\r\n\x48\x6f\x73\x74\x3a\x20";l8*l427="\r\n\x55\x70\x67"
"\x72\x61\x64\x65\x3a\x20\x77\x65\x62\x73\x6f\x63\x6b\x65\x74\r\n\x43"
"\x6f\x6e\x6e\x65\x63\x74\x69\x6f\x6e\x20\x3a\x20\x55\x70\x67\x72\x61"
"\x64\x65\r\n\x53\x65\x63\x2d\x57\x65\x62\x53\x6f\x63\x6b\x65\x74\x2d"
"\x4b\x65\x79\x3a\x20\x64\x47\x68\x6c\x49\x48\x4e\x68\x62\x58\x42\x73"
"\x5a\x53\x42\x75\x62\x32\x35\x6a\x5a\x51\x3d\x3d\r\n\r\n";l364(la->
l137,lf+5);l11 l275=l49-33-1;l29(lf+38,l131,l275);l11 l45=38+l275;l29
(lf+l45,l427,91);l45+=91;lc(!la->l42.l136(lf,l45))lh lq;la->l50=8;}ly
#endif
lc(!la->l42.l136(la->l137,8))lh lq;ly la->l50=2;la->l18=l239;la->l63=
0;la->l7.l35(F("\x53\x65\x74\x74\x69\x6e\x67\x2e\x2e\x2e\n"));lh l2;}
l6 l239:l6 l60:{l11 l25=0;le l68*l100=&la->lm.l96.l86;
#ifdef CRYPTO_ON
#ifdef WEBSOCKET
lc(la->l79==1){la->l79=2;lb*l61=l354(la->l5,l49);lc(!l61)lh lq;l25=
l61-la->l5;lc(l25==l49)lh l2;l49-=l25;l343(la->l5,la->l5+l25,l49);l25
=0;}lc(!la->l79)
#endif
l124(l100,la->l5+la->l63,la->l5+la->l63,l49);
#endif
la->l63+=l49;l72(1){l11 l46;l11 l36;
#ifdef WEBSOCKET
lc(la->l79&&la->l134){l11 l54=la->l63-l25;lc(l54<(2+4))l10;l12 l92=la
->l5[l25+1]&0x7f;lc(l92>0x7d){lc(l92==0x7f)lh lq; * ((lb* )&l92+0)=la
->l5[l25+3]; * ((lb* )&l92+1)=la->l5[l25+2];lc((l54-4)<l92)l10;l46=
l25+4;}ly{lc((l54-2)<l92)l10;l46=l25+2;}lc(l92<4)lh lq;l36=l46+l92-4;
#ifdef CRYPTO_ON
l124(l100,la->l5+l46,la->l5+l46,l92);
#endif
lo l188=0;l29(&l188,la->l5+l36,4);l100->l39=l121(la->l5+l46,l92-4,
l100->l39);lc(l100->l39!=l188){lh lq;}l25=l36+4;}ly
#endif
{lo l188;l12 l38;l11 l54=la->l63-l25;lc(l54<6)l10;l38=la->l5[l25]+(la
->l5[l25+1]<<8);lc((l11)(l38+6)>l54){lc(l54==RX_BUF_SIZE){la->l7.l35(
F("\x52\x65\x63\x65\x69\x76\x69\x6e\x67\x20\x74\x6f\x6f\x20\x6d\x75"
"\x63\x68\x20\x64\x61\x74\x61\x2c\x20\x52\x58\x20\x62\x75\x66\x66\x65"
"\x72\x20\x73\x69\x7a\x65\x20\x6d\x75\x73\x74\x20\x6e\x6f\x74\x20\x62"
"\x65\x20\x6c\x65\x73\x73\x20\x74\x68\x61\x6e\x20\x25\x69\x20\x62\x79"
"\x74\x65\x73\x2e\n"),l38+6);lh lq;}l10;}lc(la->l134){l29(&l188,la->
l5+l25+2+l38,4);l100->l39=l121(la->l5+l25+2,l38,l100->l39);lc(l100->
l39!=l188)lh lq;}ly la->l134=l2;l46=l25+2;l36=l46+l38;l25+=l38+6;}l72
(l46!=l36){l11 l414=l46;l11 l43;lb l205;lb*l21;lc(la->l42.l191()){l12
l132;l25=l46-2;l343(la->l5,la->l5+l25,la->l63-l25);la->l63-=l25;l132=
l36-l46;la->l5[0]= * ((lb* )&l132);la->l5[1]= * ((lb* )&l132+1);la->
l134=lq;lh l2;}l43=la->l5[l46++]&0x7f;lc(l43==0x7f){lb l84; * ((lb* )&
l43+0)=la->l5[l46++];l84=la->l5[l46++]; * ((lb* )&l43+1)=l84&0x0f;}lc
(la->l5[l414]&0x80)l205=la->l5[l46++];ly l205=0;l21=la->l5+l46;l46+=
l43;lc(l46>l36)lh lq;l148(l205){l6 l428:{lb l4;l77 l370=
0xffffffffffffffffLL;le l9*lt;l130 lu;le l185 l26;lc(l43<3)lh lq;l4=
l21[0];lc(l4>=la->l48)lh lq;lt=la->l3+l4;lu=l43-3;lc(lt->l127.lm.l0.
l442){lu-=8;lc(lu<0)lh lq;l29(&l370,l21+l43-8,8);}l26.l37.l51=la->
l193;l26.l37.l51|=(l21[2]<<8)|l21[1];lc(lt->lm.l20.l56==l153){lb*l36;
lb l84;l26.lw.l55=l21+3;l36=l26.lw.l55+lu;l84= *l36; *l36=0;la->l7.
l78(l240,lt,&l26); *l36=l84;}ly lc(lt->lm.l20.l56==l173){l21[1]=(lb)lu
;l21[2]=(lb)(lu>>8);l26.lw.l55=l21+3-2;la->l7.l78(l240,lt,&l26);}ly{
lc(l196(lt)!=(l12)lu)lh lq;l29(&l26.lw.l156,l21+3,lu);la->l7.l78(l240
,lt,&l26);}l10;}l6 l329:{lc(l43!=6)lh lq;l29(((lb* )&(la->l193))+2,
l21,6);l10;}l6 l377:{lb l4;le l9*lt;lc(l43!=1)lh lq;l4=l21[0];lc(l4>=
la->l48)lh lq;lt=la->l3+l4;la->l7.l78(l396,lt,0);l10;}l6 l366:{lb l4;
l12 lu;le l9*lt;le l185 l26;lc(l43<1)lh lq;l4=l21[0];lc(l4>=la->l48)lh
lq;lu=l43-1;lt=la->l3+l4;lc(lt->lm.l20.l56==l153){lb*l36;lb l84;l26.
lw.l55=l21+1;l36=l26.lw.l55+lu;l84= *l36; *l36=0;la->l7.l78(l234,lt,&
l26); *l36=l84;}ly lc(lt->lm.l20.l56==l173){ * (l21-1)=(lb)lu;l21[0]=
(lb)(lu>>8);l26.lw.l55=l21-1;la->l7.l78(l234,lt,&l26);}ly{lc(l196(lt)!=
lu)lh lq;l29(&l26.lw.l156,l21+1,lu);la->l7.l78(l234,lt,&l26);}l10;}l6
l324:{lc(l43!=2)lh lq;lc(l21[0]!=l101)lh lq;l10;}l6 l295:l6 l436:{lb
l4;le l9*lt;lc(l43!=1)lh lq;l4=l21[0];lc(l4>=la->l48)lh lq;lt=la->l3+
l4;lc(l205==l295){lt->lm.l20.l112=1;lc(l4==0)la->l7.l35(F("\x65\x6e"
"\x74\x65\x72\x65\x64\x20\x66\x69\x72\x73\x74\x20\x63\x6c\x69\x65\x6e"
"\x74\n"));ly{lc(lt->l127.lm.l0.l375)la->l7.l78(l418,lt,0);}}ly{lt->
lm.l20.l112=0;lc(l4==0)la->l7.l35(F("\x65\x78\x69\x74\x20\x6c\x61\x73"
"\x74\x20\x63\x6c\x69\x65\x6e\x74\n"));}l10;}l6 l371:{l66 l158;lc(l43
!=8)lh lq;l29(&l158,l21,8);l397=l158-(l107()-l397);l10;}l6 l437:l6
l406:l10;l6 l349:{lc(!la->l171){l11 ll;
#if ( RX_BUF_SIZE < 4096)
l426(la,RX_BUF_SIZE);
#endif
#ifdef ATTACHED_MODE
l33(ll=1;ll<la->l125;ll++){
#else
l33(ll=1;ll<la->l48;ll++){
#endif
l372(la,ll);lc(la->l3[ll].lp.l37.l0.l145!=255)l373(la,la->l7.l221[la
->l3[ll].lp.l37.l0.l145],ll);}
#ifdef ATTACHED_MODE
l33(ll=la->l125;ll<la->l48;ll++)l249(la,ll);
#endif
l443(la,0);}la->l7.l35(F("\x57\x6f\x72\x6b\x2e\x2e\x2e\n"));la->l18=
l60;la->l164=0;l10;}
#ifdef ATTACHED_MODE
l6 l416:{lb l4;l12 lu;le l9*lt;le l185 l26;lc(l43<3)lh lq;l4=l21[0];
lc(l4>=la->l48)lh lq;lu=l43-3;lt=la->l3+l4;l26.l37.l51=la->l193|((l21
[2]<<8)|l21[1]);lc(lt->lm.l20.l56==l153){lb*l36;lb l84;l26.lw.l55=l21
+3;l36=l26.lw.l55+lu;l84= *l36; *l36=0;la->l7.l78(l247,lt,&l26); *l36
=l84;}ly lc(lt->lm.l20.l56==l173){ * (l21+1)=(lb)lu; * (l21+2)=(lb)(
lu>>8);l26.lw.l55=l21+1;la->l7.l78(l247,lt,&l26);}ly{lc(l196(lt)!=lu)lh
lq;l29(&l26.lw.l156,l21+3,lu);la->l7.l78(l247,lt,&l26);}l10;}l6 l285:
{lb l4;le l9*lt;lc((l43!=4)&&(l43!=2))lh lq;l4=l21[1];lc(l4>=la->l48)lh
lq;lt=la->l3+l4;lt->lm.l20.l170=lq;lc(l43==4){lt->lm.l20.l56=l21[2];
lt->l127.lm.lp=l21[3];lt->lm.l20.l112=l2;}ly lt->lm.l20.l112=lq;l10;}
l6 l388:{lc(l43!=5)lh lq;lo l113=l21[0]; * ((lb* )&l113+1)=l21[1]; * (
(lb* )&l113+2)=l21[2]; * ((lb* )&l113+3)=l21[3];lb l265=l21[4];l33(
l11 ll=la->l125;ll<la->l48;ll++){lo l307;lc(l439(la,ll,&l307)){lc(
l307==l113){le l9*lt=la->l3+ll;lc((l265==l290)&&(lt->lm.l20.l112==lq)&&
(lt->lm.l20.l170==lq))l249(la,ll);ly lc((l265!=l290)&&(l265!=l357)){
lt->lm.l20.l112=lq;la->l7.l78(l409,lt,0);}}}}l10;}
#endif
l225:lh lq;}}}lc(l25){la->l63-=l25;l343(la->l5,la->l5+l25,la->l63);}}
}lh l2;}l16 lr l209(le l1*la){l11 ll;
#ifdef ATTACHED_MODE
l33(ll=0;ll<la->l125;ll++){
#else
l33(ll=0;ll<la->l48;ll++){
#endif
le l9*lt=la->l3+ll;lc(lt->lm.l133.l149){lt->lp.lw.l64->l281(lt->lp.lw
.l64->l135);lt->lm.l133.l149=0;}lt->lm.l20.l112=0;}la->l42.l292();la
->l18=l91;la->l171=lq;la->l63=0;la->l134=l2;la->l183=la->l183-
0x10000L;}l16 lr l389(le l1*la,l12 l162){lb*lf=l40(la,4);lf[0]=0x82;
lf[1]=l358;lf[2]= * ((lb* )&l162);lf[3]= * ((lb* )&l162+1);l52(la,4,
lq);l210(la,l2);}l16 l30 l424 l412(le l1*la){l66 l158=l107();l66 l315
=la->l70;l19 l402=lq;lb l277;lc(la->l18==l91){lc(la->l70>l158)lh l91;
}la->l70=0;l277=la->l18;lc(!l399(la,&l402)){la->l7.l35(F("\x44\x69"
"\x73\x63\x6f\x6e\x6e\x65\x63\x74\x65\x64\n"));l209(la);lc(!la->l70)la
->l70=l158+2000;lh l177;}lc(la->l18==l60){lc(l277!=l60)lh l351;la->
l70=l315;lc(l2){l11 ll;
#ifdef ATTACHED_MODE
l33(ll=0;ll<la->l125;ll++){
#else
l33(ll=0;ll<la->l48;ll++){
#endif
le l9*lt=la->l3+ll;lc(lt->lm.l133.l149){lc(la->l42.l191())lh l243;
l208(la,lt,l172);}}}lc(la->l197&&(l315<l158))l210(la,lq);lc(la->l42.
l191())lh l243;lh l60;}lh l91;}l19 l483(le l90*ln,l206 l17,l165 l32){
lh l330((le l9* )ln,l17,l32);}l19 l515(le l90*ln,l195 l17,l165 l32){
lh l378((le l9* )ln,l17,l32);}l19 l481(le l90*ln,lv lr*l244,l165 l32){
lh l380((le l9* )ln,l244,l32);}l19 l495(le l90*ln,l165 l32){lh l362((
le l9* )ln,l32);}l19 l548(le l69*la,le l484*l166,le l503*l272){((le
l163* )l166)->l35(F("\x4d\x67\x74\x43\x6c\x69\x65\x6e\x74\x20\x76\x32"
"\x2e\x30\x2c\x20\x30\x35\x2f\x56\x49\x2f\x32\x30\x32\x32\n"));lc(
offsetof(le l69,l3)!=offsetof(le l1,l3)){l11 l360=offsetof(le l1,l3);
((le l163* )l166)->l35(F("\x49\x6e\x20\x74\x68\x65\x20\x66\x69\x6c"
"\x65\x20\"\x4d\x67\x74\x43\x6c\x69\x65\x6e\x74\x2e\x68\"\x20\x69\x6e"
"\x20\x6c\x69\x6e\x65\x20\"\x23\x64\x65\x66\x69\x6e\x65\x20\x4d\x47"
"\x54\x5f\x43\x4f\x4e\x53\x54\x41\x4e\x54\x20\x25\x69\"\n\x79\x6f\x75"
"\x20\x6e\x65\x65\x64\x20\x74\x6f\x20\x73\x65\x74\x20\x74\x68\x65\x20"
"\x6e\x75\x6d\x62\x65\x72\x20\x25\x69\x20\x21\n"),(l11)(l81(la->l501)),
(l11)l360);lh lq;}((le l163* )l166)->l35(F("\x49\x6e\x69\x74\n"));
l407((le l1* )la,(le l163* )l166,(le l262* )l272);lh l2;}lr l528(le
l69*la,lv l8*l228,l30 l526 l386){le l1*lx=(le l1* )la;lx->l266=l228;
lx->l236=l386;lc(lx->l18==l93){lc(lx->l171){lv l8*l131;l8 l257[12+3+1
];lx->l7.l35(F("\x52\x65\x73\x74\x61\x72\x74\x20\x73\x65\x73\x73\x69"
"\x6f\x6e\n"));l278(lx,l257,&l131);lc(!lx->l42.l238(l131,lx->l128)){
lx->l7.l35(F("\x4e\x6f\x20\x63\x6f\x6e\x6e\x65\x63\x74\x69\x6f\x6e"
"\x20\x77\x69\x74\x68\x20\x74\x68\x65\x20\x73\x65\x72\x76\x69\x63\x65"
"\n"));lx->l18=l91;lx->l171=lq;lx->l70=l107()+2000;}l291(lx);lc(!lx->
l42.l136(lx->l137,8)){lx->l7.l35(F("\x44\x69\x73\x63\x6f\x6e\x6e\x65"
"\x63\x74\x65\x64\n"));l209(lx);lx->l70=l107()+2000;lh;}ly{lx->l18=
l239;lx->l63=0;}}ly{lx->l18=l91;lx->l7.l35(F("\x53\x74\x61\x72\x74"
"\n"));}}}lr l467(le l69*la,l12 l162){le l1*lx=(le l1* )la;lc((lx->
l18!=l93)&&(lx->l18!=l177)){lc(lx->l18!=l91){lc((l162)&&(lx->l18==l60
)){l165 l259;l389(lx,l162);l259=l107();lx->l70=l259+1000;lo l403=l162
 *1000;lx->l193=l259+l403;lx->l18=l177;}ly{l209(lx);lx->l18=l93;}}lx
->l7.l35(F("\x53\x74\x6f\x70\n"));}}l30 l119 l473(le l69*la){le l1*lx
=(le l1* )la;lc(lx->l18==l177){lc(lx->l70<l107()){l209(lx);lx->l18=
l93;lx->l171=l2;}ly lh(l30 l119)l177;}lc(lx->l18==l93)lh(l30 l119)l93
;lh(l30 l119)l412((le l1* )la);}l30 l119 l447(le l69*la){le l1*lx=(le
l1* )la;lc(lx->l18==l60){lc(lx->l42.l191())lh(l30 l119)l243;ly lh(l30
l119)l60;}lc(lx->l18==l93)lh(l30 l119)l93;lh(l30 l119)l91;}lr l489(le
l69*la,le l90*ln){le l1*lx=(le l1* )la;lc(lx->l18!=l60)lh;l344(lx,(le
l9* )ln);}lr l480(le l69*la,le l306*l97,lv l8*l139,l165 l32,...){l479
l215;le l9*l190;le l1*lx=(le l1* )la;lc(lx->l18!=l60)lh;l284(lx,(le l9
 * )l97,l139,l32);l450(l215,l32);l190=l391(l215,le l9* );l72(l190){
l129 ll=(lb* )l190-(lb* )la->l3;lc(ll%l81(le l9))l10;lc((ll<0)||(ll>=
(l129)(lx->l48*l81(le l9))))l10;l344(lx,l190);l190=l391(l215,le l9* );
}l491(l215);l342(lx,(le l9* )l97);}lr l471(le l69*la,le l306*l97,lv l8
 *l139,l165 l32){le l1*lx=(le l1* )la;lc(lx->l18!=l60)lh;l284(lx,(le
l9* )l97,l139,l32);}lr l546(le l69*la,le l306*l97){le l1*lx=(le l1* )la
;lc(lx->l18!=l60)lh;l342(lx,(le l9* )l97);}lr l452(le l69*la,le l90*
ln,l30 l425 l65){le l1*lx=(le l1* )la;lc(lx->l18!=l60)lh;l422(lx,(le
l9* )ln,(l30 l192)l65);}lr l523(le l69*la,le l90*ln,l30 l425 l65){le
l1*lx=(le l1* )la;lc(lx->l18!=l60)lh;l446(lx,(le l9* )ln,(l30 l192)l65
);}le l90*l504(le l69*la,lv l8*l143,l30 l519 l186,lb l252,l12 l231,le
l529*l199){lh(le l90* )l355((le l1* )la,l143,(l30 l301)l186,l252,l231
,(le l255* )l199);}
#ifdef ATTACHED_MODE
le l90*l537(le l69*la,lv l8*l143){lh(le l90* )l394((le l1* )la,l143);
}lr l493(le l69*la){l369((le l1* )la);}
#endif
