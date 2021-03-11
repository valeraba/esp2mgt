/*
Copyright © 2015, BVAgile. All rights reserved.
Contacts: <bvagile@gmail.com>
*/

#include"MgtClient.h"
#define ld struct
#define lo __uint32
#define lb __uint8
#define lr void
#define lv const
#define l11 static
#define le if
#define lk return
#define l33 memcpy
#define l82 while
#define l9 char
#define l232 unsigned
#define l22 int
#define l212 strlen
#define l515 strncmp
#define l31 for
#define l495 continue
#define l386 memset
#define l71 sizeof
#define l1 else
#define l170 crc32
#define l75 __uint64
#define l114 union
#define l29 enum
#define l15 __uint16
#define l17 bool
#define l318 rand
#define lq false
#define l524 memcmp
#define l2 true
#define l516 strchr
#define l10 break
#define l241 typedef
#define l200 __int64
#define l121 __int16
#define l229 read
#define l274 abort
#define l407 __int8
#define l120 __int32
#define l301 float
#define l188 double
#define l153 switch
#define l7 case
#define l197 default
#define l349 updateTime
#define l231 open
#define l284 close
#define l4 m_signals
#define l122 rem
#define l100 getUTCTime
#define ls signal
#define l344 strrchr
#define l373 atoi
#define l335 memmove
#define l146 time
#define l384 shiftTime
#define l475 signal_updateInt
#define l84 Signal
#define l161 TimeStamp
#define l503 signal_updateDouble
#define l466 signal_updatePtr
#define l480 signal_updateTime
#define l530 mgt_init
#define l59 MgtClient
#define l471 DeviceConfig
#define l492 PortableSocket
#define l489 m_reserv
#define l514 mgt_start
#define l452 mgt_stop
#define l111 MgtState
#define l463 mgt_run
#define l435 mgt_getState
#define l477 mgt_send
#define l465 mgt_eventSend
#define l297 Event
#define l470 va_list
#define l434 va_start
#define l376 va_arg
#define l478 va_end
#define l456 mgt_eventBegin
#define l528 mgt_eventEnd
#define l440 mgt_readAns
#define l412 ErrorCode
#define l509 mgt_writeAns
#define l493 mgt_createSignal
#define l507 SignalType
#define l517 ChunkedTransfer
#define l523 mgt_attachSignal
#define l482 mgt_detachAll


ld l108{lo l78[2];lo l30[4];lb l257[64];};lr l119(ld l108*ly);lr l37(
ld l108*ly,lv lb*l8,lo l64);lr l137(lb l52[16],ld l108*ly);lr l119(ld
l108*ly){ly->l78[0]=0;ly->l78[1]=0;ly->l30[0]=0x67452301;ly->l30[1]=
0xEFCDAB89;ly->l30[2]=0x98BADCFE;ly->l30[3]=0x10325476;}l11 lr l307(
ld l108*ly,lv lb lt[64]){lo lc[16],lh,lg,lf,li;{(lc[0])=((lo)(lt)[(0)]
)|((lo)(lt)[(0)+1]<<8)|((lo)(lt)[(0)+2]<<16)|((lo)(lt)[(0)+3]<<24);};
{(lc[1])=((lo)(lt)[(4)])|((lo)(lt)[(4)+1]<<8)|((lo)(lt)[(4)+2]<<16)|(
(lo)(lt)[(4)+3]<<24);};{(lc[2])=((lo)(lt)[(8)])|((lo)(lt)[(8)+1]<<8)|
((lo)(lt)[(8)+2]<<16)|((lo)(lt)[(8)+3]<<24);};{(lc[3])=((lo)(lt)[(12)]
)|((lo)(lt)[(12)+1]<<8)|((lo)(lt)[(12)+2]<<16)|((lo)(lt)[(12)+3]<<24);
};{(lc[4])=((lo)(lt)[(16)])|((lo)(lt)[(16)+1]<<8)|((lo)(lt)[(16)+2]<<
16)|((lo)(lt)[(16)+3]<<24);};{(lc[5])=((lo)(lt)[(20)])|((lo)(lt)[(20)+
1]<<8)|((lo)(lt)[(20)+2]<<16)|((lo)(lt)[(20)+3]<<24);};{(lc[6])=((lo)(
lt)[(24)])|((lo)(lt)[(24)+1]<<8)|((lo)(lt)[(24)+2]<<16)|((lo)(lt)[(24
)+3]<<24);};{(lc[7])=((lo)(lt)[(28)])|((lo)(lt)[(28)+1]<<8)|((lo)(lt)[
(28)+2]<<16)|((lo)(lt)[(28)+3]<<24);};{(lc[8])=((lo)(lt)[(32)])|((lo)(
lt)[(32)+1]<<8)|((lo)(lt)[(32)+2]<<16)|((lo)(lt)[(32)+3]<<24);};{(lc[
9])=((lo)(lt)[(36)])|((lo)(lt)[(36)+1]<<8)|((lo)(lt)[(36)+2]<<16)|((
lo)(lt)[(36)+3]<<24);};{(lc[10])=((lo)(lt)[(40)])|((lo)(lt)[(40)+1]<<
8)|((lo)(lt)[(40)+2]<<16)|((lo)(lt)[(40)+3]<<24);};{(lc[11])=((lo)(lt
)[(44)])|((lo)(lt)[(44)+1]<<8)|((lo)(lt)[(44)+2]<<16)|((lo)(lt)[(44)+
3]<<24);};{(lc[12])=((lo)(lt)[(48)])|((lo)(lt)[(48)+1]<<8)|((lo)(lt)[
(48)+2]<<16)|((lo)(lt)[(48)+3]<<24);};{(lc[13])=((lo)(lt)[(52)])|((lo
)(lt)[(52)+1]<<8)|((lo)(lt)[(52)+2]<<16)|((lo)(lt)[(52)+3]<<24);};{(
lc[14])=((lo)(lt)[(56)])|((lo)(lt)[(56)+1]<<8)|((lo)(lt)[(56)+2]<<16)|
((lo)(lt)[(56)+3]<<24);};{(lc[15])=((lo)(lt)[(60)])|((lo)(lt)[(60)+1]
<<8)|((lo)(lt)[(60)+2]<<16)|((lo)(lt)[(60)+3]<<24);};lh=ly->l30[0];lg
=ly->l30[1];lf=ly->l30[2];li=ly->l30[3];{lh+=(li^(lg&(lf^li)))+lc[0]+
0xD76AA478;lh=((lh<<7)|((lh&0xFFFFFFFF)>>(32-7)))+lg;};{li+=(lf^(lh&(
lg^lf)))+lc[1]+0xE8C7B756;li=((li<<12)|((li&0xFFFFFFFF)>>(32-12)))+lh
;};{lf+=(lg^(li&(lh^lg)))+lc[2]+0x242070DB;lf=((lf<<17)|((lf&
0xFFFFFFFF)>>(32-17)))+li;};{lg+=(lh^(lf&(li^lh)))+lc[3]+0xC1BDCEEE;
lg=((lg<<22)|((lg&0xFFFFFFFF)>>(32-22)))+lf;};{lh+=(li^(lg&(lf^li)))+
lc[4]+0xF57C0FAF;lh=((lh<<7)|((lh&0xFFFFFFFF)>>(32-7)))+lg;};{li+=(lf
^(lh&(lg^lf)))+lc[5]+0x4787C62A;li=((li<<12)|((li&0xFFFFFFFF)>>(32-12
)))+lh;};{lf+=(lg^(li&(lh^lg)))+lc[6]+0xA8304613;lf=((lf<<17)|((lf&
0xFFFFFFFF)>>(32-17)))+li;};{lg+=(lh^(lf&(li^lh)))+lc[7]+0xFD469501;
lg=((lg<<22)|((lg&0xFFFFFFFF)>>(32-22)))+lf;};{lh+=(li^(lg&(lf^li)))+
lc[8]+0x698098D8;lh=((lh<<7)|((lh&0xFFFFFFFF)>>(32-7)))+lg;};{li+=(lf
^(lh&(lg^lf)))+lc[9]+0x8B44F7AF;li=((li<<12)|((li&0xFFFFFFFF)>>(32-12
)))+lh;};{lf+=(lg^(li&(lh^lg)))+lc[10]+0xFFFF5BB1;lf=((lf<<17)|((lf&
0xFFFFFFFF)>>(32-17)))+li;};{lg+=(lh^(lf&(li^lh)))+lc[11]+0x895CD7BE;
lg=((lg<<22)|((lg&0xFFFFFFFF)>>(32-22)))+lf;};{lh+=(li^(lg&(lf^li)))+
lc[12]+0x6B901122;lh=((lh<<7)|((lh&0xFFFFFFFF)>>(32-7)))+lg;};{li+=(
lf^(lh&(lg^lf)))+lc[13]+0xFD987193;li=((li<<12)|((li&0xFFFFFFFF)>>(32
-12)))+lh;};{lf+=(lg^(li&(lh^lg)))+lc[14]+0xA679438E;lf=((lf<<17)|((
lf&0xFFFFFFFF)>>(32-17)))+li;};{lg+=(lh^(lf&(li^lh)))+lc[15]+
0x49B40821;lg=((lg<<22)|((lg&0xFFFFFFFF)>>(32-22)))+lf;};{lh+=(lf^(li
&(lg^lf)))+lc[1]+0xF61E2562;lh=((lh<<5)|((lh&0xFFFFFFFF)>>(32-5)))+lg
;};{li+=(lg^(lf&(lh^lg)))+lc[6]+0xC040B340;li=((li<<9)|((li&
0xFFFFFFFF)>>(32-9)))+lh;};{lf+=(lh^(lg&(li^lh)))+lc[11]+0x265E5A51;
lf=((lf<<14)|((lf&0xFFFFFFFF)>>(32-14)))+li;};{lg+=(li^(lh&(lf^li)))+
lc[0]+0xE9B6C7AA;lg=((lg<<20)|((lg&0xFFFFFFFF)>>(32-20)))+lf;};{lh+=(
lf^(li&(lg^lf)))+lc[5]+0xD62F105D;lh=((lh<<5)|((lh&0xFFFFFFFF)>>(32-5
)))+lg;};{li+=(lg^(lf&(lh^lg)))+lc[10]+0x02441453;li=((li<<9)|((li&
0xFFFFFFFF)>>(32-9)))+lh;};{lf+=(lh^(lg&(li^lh)))+lc[15]+0xD8A1E681;
lf=((lf<<14)|((lf&0xFFFFFFFF)>>(32-14)))+li;};{lg+=(li^(lh&(lf^li)))+
lc[4]+0xE7D3FBC8;lg=((lg<<20)|((lg&0xFFFFFFFF)>>(32-20)))+lf;};{lh+=(
lf^(li&(lg^lf)))+lc[9]+0x21E1CDE6;lh=((lh<<5)|((lh&0xFFFFFFFF)>>(32-5
)))+lg;};{li+=(lg^(lf&(lh^lg)))+lc[14]+0xC33707D6;li=((li<<9)|((li&
0xFFFFFFFF)>>(32-9)))+lh;};{lf+=(lh^(lg&(li^lh)))+lc[3]+0xF4D50D87;lf
=((lf<<14)|((lf&0xFFFFFFFF)>>(32-14)))+li;};{lg+=(li^(lh&(lf^li)))+lc
[8]+0x455A14ED;lg=((lg<<20)|((lg&0xFFFFFFFF)>>(32-20)))+lf;};{lh+=(lf
^(li&(lg^lf)))+lc[13]+0xA9E3E905;lh=((lh<<5)|((lh&0xFFFFFFFF)>>(32-5)))+
lg;};{li+=(lg^(lf&(lh^lg)))+lc[2]+0xFCEFA3F8;li=((li<<9)|((li&
0xFFFFFFFF)>>(32-9)))+lh;};{lf+=(lh^(lg&(li^lh)))+lc[7]+0x676F02D9;lf
=((lf<<14)|((lf&0xFFFFFFFF)>>(32-14)))+li;};{lg+=(li^(lh&(lf^li)))+lc
[12]+0x8D2A4C8A;lg=((lg<<20)|((lg&0xFFFFFFFF)>>(32-20)))+lf;};{lh+=(
lg^lf^li)+lc[5]+0xFFFA3942;lh=((lh<<4)|((lh&0xFFFFFFFF)>>(32-4)))+lg;
};{li+=(lh^lg^lf)+lc[8]+0x8771F681;li=((li<<11)|((li&0xFFFFFFFF)>>(32
-11)))+lh;};{lf+=(li^lh^lg)+lc[11]+0x6D9D6122;lf=((lf<<16)|((lf&
0xFFFFFFFF)>>(32-16)))+li;};{lg+=(lf^li^lh)+lc[14]+0xFDE5380C;lg=((lg
<<23)|((lg&0xFFFFFFFF)>>(32-23)))+lf;};{lh+=(lg^lf^li)+lc[1]+
0xA4BEEA44;lh=((lh<<4)|((lh&0xFFFFFFFF)>>(32-4)))+lg;};{li+=(lh^lg^lf
)+lc[4]+0x4BDECFA9;li=((li<<11)|((li&0xFFFFFFFF)>>(32-11)))+lh;};{lf
+=(li^lh^lg)+lc[7]+0xF6BB4B60;lf=((lf<<16)|((lf&0xFFFFFFFF)>>(32-16)))+
li;};{lg+=(lf^li^lh)+lc[10]+0xBEBFBC70;lg=((lg<<23)|((lg&0xFFFFFFFF)>>
(32-23)))+lf;};{lh+=(lg^lf^li)+lc[13]+0x289B7EC6;lh=((lh<<4)|((lh&
0xFFFFFFFF)>>(32-4)))+lg;};{li+=(lh^lg^lf)+lc[0]+0xEAA127FA;li=((li<<
11)|((li&0xFFFFFFFF)>>(32-11)))+lh;};{lf+=(li^lh^lg)+lc[3]+0xD4EF3085
;lf=((lf<<16)|((lf&0xFFFFFFFF)>>(32-16)))+li;};{lg+=(lf^li^lh)+lc[6]+
0x04881D05;lg=((lg<<23)|((lg&0xFFFFFFFF)>>(32-23)))+lf;};{lh+=(lg^lf^
li)+lc[9]+0xD9D4D039;lh=((lh<<4)|((lh&0xFFFFFFFF)>>(32-4)))+lg;};{li
+=(lh^lg^lf)+lc[12]+0xE6DB99E5;li=((li<<11)|((li&0xFFFFFFFF)>>(32-11)))+
lh;};{lf+=(li^lh^lg)+lc[15]+0x1FA27CF8;lf=((lf<<16)|((lf&0xFFFFFFFF)>>
(32-16)))+li;};{lg+=(lf^li^lh)+lc[2]+0xC4AC5665;lg=((lg<<23)|((lg&
0xFFFFFFFF)>>(32-23)))+lf;};{lh+=(lf^(lg|~li))+lc[0]+0xF4292244;lh=((
lh<<6)|((lh&0xFFFFFFFF)>>(32-6)))+lg;};{li+=(lg^(lh|~lf))+lc[7]+
0x432AFF97;li=((li<<10)|((li&0xFFFFFFFF)>>(32-10)))+lh;};{lf+=(lh^(li
|~lg))+lc[14]+0xAB9423A7;lf=((lf<<15)|((lf&0xFFFFFFFF)>>(32-15)))+li;
};{lg+=(li^(lf|~lh))+lc[5]+0xFC93A039;lg=((lg<<21)|((lg&0xFFFFFFFF)>>
(32-21)))+lf;};{lh+=(lf^(lg|~li))+lc[12]+0x655B59C3;lh=((lh<<6)|((lh&
0xFFFFFFFF)>>(32-6)))+lg;};{li+=(lg^(lh|~lf))+lc[3]+0x8F0CCC92;li=((
li<<10)|((li&0xFFFFFFFF)>>(32-10)))+lh;};{lf+=(lh^(li|~lg))+lc[10]+
0xFFEFF47D;lf=((lf<<15)|((lf&0xFFFFFFFF)>>(32-15)))+li;};{lg+=(li^(lf
|~lh))+lc[1]+0x85845DD1;lg=((lg<<21)|((lg&0xFFFFFFFF)>>(32-21)))+lf;}
;{lh+=(lf^(lg|~li))+lc[8]+0x6FA87E4F;lh=((lh<<6)|((lh&0xFFFFFFFF)>>(
32-6)))+lg;};{li+=(lg^(lh|~lf))+lc[15]+0xFE2CE6E0;li=((li<<10)|((li&
0xFFFFFFFF)>>(32-10)))+lh;};{lf+=(lh^(li|~lg))+lc[6]+0xA3014314;lf=((
lf<<15)|((lf&0xFFFFFFFF)>>(32-15)))+li;};{lg+=(li^(lf|~lh))+lc[13]+
0x4E0811A1;lg=((lg<<21)|((lg&0xFFFFFFFF)>>(32-21)))+lf;};{lh+=(lf^(lg
|~li))+lc[4]+0xF7537E82;lh=((lh<<6)|((lh&0xFFFFFFFF)>>(32-6)))+lg;};{
li+=(lg^(lh|~lf))+lc[11]+0xBD3AF235;li=((li<<10)|((li&0xFFFFFFFF)>>(
32-10)))+lh;};{lf+=(lh^(li|~lg))+lc[2]+0x2AD7D2BB;lf=((lf<<15)|((lf&
0xFFFFFFFF)>>(32-15)))+li;};{lg+=(li^(lf|~lh))+lc[9]+0xEB86D391;lg=((
lg<<21)|((lg&0xFFFFFFFF)>>(32-21)))+lf;};ly->l30[0]+=lh;ly->l30[1]+=
lg;ly->l30[2]+=lf;ly->l30[3]+=li;}lr l37(ld l108*ly,lv lb*l8,lo l64){
lo l156,l166;le(!l64)lk;l156=ly->l78[0]&0x3F;l166=64-l156;ly->l78[0]
+=l64;ly->l78[0]&=0xFFFFFFFF;le(ly->l78[0]<l64)ly->l78[1]++;le(l156&&
l64>=l166){l33((lr* )(ly->l257+l156),(lr* )l8,l166);l307(ly,ly->l257);
l64-=l166;l8+=l166;l156=0;}l82(l64>=64){l307(ly,l8);l64-=64;l8+=64;}
le(l64)l33((lr* )(ly->l257+l156),(lr* )l8,l64);}l11 lb l391[64]={0x80
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};lr l137(lb
l52[16],ld l108*ly){lo l206,l312;lo l179,l189;lb l97[8];l179=(ly->l78
[0]>>29)|(ly->l78[1]<<3);l189=(ly->l78[0]<<3);{(l97)[(0)]=(lb)((l189));
(l97)[(0)+1]=(lb)((l189)>>8);(l97)[(0)+2]=(lb)((l189)>>16);(l97)[(0)+
3]=(lb)((l189)>>24);};{(l97)[(4)]=(lb)((l179));(l97)[(4)+1]=(lb)((
l179)>>8);(l97)[(4)+2]=(lb)((l179)>>16);(l97)[(4)+3]=(lb)((l179)>>24);
};l206=ly->l78[0]&0x3F;l312=(l206<56)?(56-l206):(120-l206);l37(ly,
l391,l312);l37(ly,l97,8);{(l52)[(0)]=(lb)((ly->l30[0]));(l52)[(0)+1]=
(lb)((ly->l30[0])>>8);(l52)[(0)+2]=(lb)((ly->l30[0])>>16);(l52)[(0)+3
]=(lb)((ly->l30[0])>>24);};{(l52)[(4)]=(lb)((ly->l30[1]));(l52)[(4)+1
]=(lb)((ly->l30[1])>>8);(l52)[(4)+2]=(lb)((ly->l30[1])>>16);(l52)[(4)+
3]=(lb)((ly->l30[1])>>24);};{(l52)[(8)]=(lb)((ly->l30[2]));(l52)[(8)+
1]=(lb)((ly->l30[2])>>8);(l52)[(8)+2]=(lb)((ly->l30[2])>>16);(l52)[(8
)+3]=(lb)((ly->l30[2])>>24);};{(l52)[(12)]=(lb)((ly->l30[3]));(l52)[(
12)+1]=(lb)((ly->l30[3])>>8);(l52)[(12)+2]=(lb)((ly->l30[3])>>16);(
l52)[(12)+3]=(lb)((ly->l30[3])>>24);};}lb*l320(lv l9*l103,lv l9*l289){
lv l9*l101, *l149;l11 lb l90[16];l232 l22 ll,l195,l102;ld l108 ly,l69
;l22 l187;l102=l212(l103);l101=l289;le(l515(l101,"\x24\x31\x24",3)==0
)l101+=3;l31(l149=l101; *l149!='\0'&& *l149!='$'&&l149<(l101+8);l149
++)l495;l195=l149-l101;l119(&ly);l37(&ly,(lv lb* )l103,l102);l37(&ly,
(lv lb* )"\x24\x31\x24",3);l37(&ly,(lv lb* )l101,l195);l119(&l69);l37
(&l69,(lv lb* )l103,l102);l37(&l69,(lv lb* )l101,l195);l37(&l69,(lv lb
 * )l103,l102);l137(l90,&l69);l31(l187=l102;l187>0;l187-=16)l37(&ly,
l90,(l232 l22)(l187>16?16:l187));l386(l90,0,l71(l90));l31(ll=l102;ll
!=0;ll>>=1)le((ll&1)!=0)l37(&ly,l90,1);l1 l37(&ly,(lv lb* )l103,1);
l137(l90,&ly);l31(ll=0;ll<1000;ll++){l119(&l69);le((ll&1)!=0)l37(&l69
,(lv lb* )l103,l102);l1 l37(&l69,l90,16);le((ll%3)!=0)l37(&l69,(lv lb
 * )l101,l195);le((ll%7)!=0)l37(&l69,(lv lb* )l103,l102);le((ll&1)!=0
)l37(&l69,l90,16);l1 l37(&l69,(lv lb* )l103,l102);l137(l90,&l69);}lk
l90;}



#ifdef CRYPTO_ON
#define l21( l105, l245) (( lo)(( l105) + ( l245)))
#define l221( l105) ( l21(( l105),1))
ld l98{lo l8[16];};lr l216(lb l157[64],lv lo l8[16]);lr l397(ld l98*
lc,lv lb*l215,lb*lf,lo l81);lr l304(ld l98*lc,lv lb*l63);lr l330(ld
l98*lc,lv lb*l264);
#endif
#ifdef CRYPTO_ON
#define l24( l105, lf) ( ROTL32( l105, lf))
#define l25( l105, l245) (( l105) ^ ( l245))
#define l334( l126, l105) ((( lo  *  )( l126))[0] = l105)
#define l58( l126) ((( lo  *  )( l126))[0])
lr l216(lb l157[64],lv lo l8[16]){lo lc[16];l22 ll;l31(ll=0;ll<16;++
ll)lc[ll]=l8[ll];l31(ll=20;ll>0;ll-=2){lc[4]=l25(lc[4],l24(l21(lc[0],
lc[12]),7));lc[8]=l25(lc[8],l24(l21(lc[4],lc[0]),9));lc[12]=l25(lc[12
],l24(l21(lc[8],lc[4]),13));lc[0]=l25(lc[0],l24(l21(lc[12],lc[8]),18));
lc[9]=l25(lc[9],l24(l21(lc[5],lc[1]),7));lc[13]=l25(lc[13],l24(l21(lc
[9],lc[5]),9));lc[1]=l25(lc[1],l24(l21(lc[13],lc[9]),13));lc[5]=l25(
lc[5],l24(l21(lc[1],lc[13]),18));lc[14]=l25(lc[14],l24(l21(lc[10],lc[
6]),7));lc[2]=l25(lc[2],l24(l21(lc[14],lc[10]),9));lc[6]=l25(lc[6],
l24(l21(lc[2],lc[14]),13));lc[10]=l25(lc[10],l24(l21(lc[6],lc[2]),18));
lc[3]=l25(lc[3],l24(l21(lc[15],lc[11]),7));lc[7]=l25(lc[7],l24(l21(lc
[3],lc[15]),9));lc[11]=l25(lc[11],l24(l21(lc[7],lc[3]),13));lc[15]=
l25(lc[15],l24(l21(lc[11],lc[7]),18));lc[1]=l25(lc[1],l24(l21(lc[0],
lc[3]),7));lc[2]=l25(lc[2],l24(l21(lc[1],lc[0]),9));lc[3]=l25(lc[3],
l24(l21(lc[2],lc[1]),13));lc[0]=l25(lc[0],l24(l21(lc[3],lc[2]),18));
lc[6]=l25(lc[6],l24(l21(lc[5],lc[4]),7));lc[7]=l25(lc[7],l24(l21(lc[6
],lc[5]),9));lc[4]=l25(lc[4],l24(l21(lc[7],lc[6]),13));lc[5]=l25(lc[5
],l24(l21(lc[4],lc[7]),18));lc[11]=l25(lc[11],l24(l21(lc[10],lc[9]),7
));lc[8]=l25(lc[8],l24(l21(lc[11],lc[10]),9));lc[9]=l25(lc[9],l24(l21
(lc[8],lc[11]),13));lc[10]=l25(lc[10],l24(l21(lc[9],lc[8]),18));lc[12
]=l25(lc[12],l24(l21(lc[15],lc[14]),7));lc[13]=l25(lc[13],l24(l21(lc[
12],lc[15]),9));lc[14]=l25(lc[14],l24(l21(lc[13],lc[12]),13));lc[15]=
l25(lc[15],l24(l21(lc[14],lc[13]),18));}l31(ll=0;ll<16;++ll)lc[ll]=
l21(lc[ll],l8[ll]);l31(ll=0;ll<16;++ll)l334(l157+4*ll,lc[ll]);}l11 lv
l9*l218="\x65\x78\x70\x61\x6e\x64\x20\x33\x32\x2d\x62\x79\x74\x65\x20"
"\x6b";lr l304(ld l98*lc,lv lb*l63){lc->l8[1]=l58(l63+0);lc->l8[2]=
l58(l63+4);lc->l8[3]=l58(l63+8);lc->l8[4]=l58(l63+12);lc->l8[11]=l58(
l63+16);lc->l8[12]=l58(l63+20);lc->l8[13]=l58(l63+24);lc->l8[14]=l58(
l63+28);lc->l8[0]=l58(l218+0);lc->l8[5]=l58(l218+4);lc->l8[10]=l58(
l218+8);lc->l8[15]=l58(l218+12);}lr l330(ld l98*lc,lv lb*l264){lc->l8
[6]=l58(l264+0);lc->l8[7]=l58(l264+4);lc->l8[8]=0;lc->l8[9]=0;}lr l397
(ld l98*lc,lv lb*l215,lb*lf,lo l81){lb l157[64];l232 l22 ll;le(!l81)lk
;l31(;;){l216(l157,lc->l8);lc->l8[8]=l221(lc->l8[8]);le(!lc->l8[8]){
lc->l8[9]=l221(lc->l8[9]);}le(l81<=64){l31(ll=0;ll<l81;++ll)lf[ll]=
l215[ll]^l157[ll];lk;}l31(ll=0;ll<64;++ll)lf[ll]=l215[ll]^l157[ll];
l81-=64;lf+=64;l215+=64;}}
#endif
#ifdef CRYPTO_ON
ld l62{lb l47[64];lo l48;lb l67;ld l98 l76;};lr l372(ld l62*l20,ld l98
 *l319);lr l207(ld l62*l20,lv lb*l113);lr l219(ld l62*l20,lv lb*l295);
lr l159(ld l62*l20,lv lb*l116,lb*l72,lo l19);
#else
ld l62{lo l48;};
#endif
lo l170(lb*l131,lo l331,lo l79);
#ifdef CRYPTO_ON
lr l372(ld l62*l20,ld l98*l319){l20->l76= *l319;l20->l67=0;l20->l48=0
;}lr l207(ld l62*l20,lv lb*l113){l304(&l20->l76,l113);}lr l219(ld l62
 *l20,lv lb*l295){l330(&l20->l76,l295);l20->l67=0;l20->l48=0;}lr l159
(ld l62*l20,lv lb*l116,lb*l72,lo l19){l232 l22 ll;le(l20->l67){lb*lt=
l20->l47+64-l20->l67;le(l19>=l20->l67){l19-=l20->l67;l31(ll=0;ll<l20
->l67;++ll)l72[ll]=l116[ll]^lt[ll];l116+=l20->l67;l72+=l20->l67;l20->
l67=0;}l1{l20->l67-=l19;l31(ll=0;ll<l19;++ll)l72[ll]=l116[ll]^lt[ll];
l19=0;}}le(!l19)lk;l31(;;){l216((lb* )l20->l47,l20->l76.l8);l20->l76.
l8[8]=l221(l20->l76.l8[8]);le(!l20->l76.l8[8])l20->l76.l8[9]=l221(l20
->l76.l8[9]);le(l19<=64){l31(ll=0;ll<l19;++ll)l72[ll]=l116[ll]^l20->
l47[ll];l20->l67=64-l19;lk;}l31(ll=0;ll<64;++ll)l72[ll]=l116[ll]^l20
->l47[ll];l19-=64;l116+=64;l72+=64;}}
#endif
l11
#ifdef ARDUINO
__flash
#endif
lv lo l255[256]={0x00000000,0x77073096,0xee0e612c,0x990951ba,
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
l170(lb*l131,lo l331,lo l79){l82(l331--)
#ifdef ARDUINO
#ifdef pgm_read_dword_far
l79=pgm_read_dword_far(l255+((l79^ *l131++)&0xff))^(l79>>8);
#else
l79=pgm_read_dword(l255+((l79^ *l131++)&0xff))^(l79>>8);
#endif
#else
l79=l255[(l79^ *l131++)&0xff]^(l79>>8);
#endif
lk l79^0xffffffff;}
lb*l320(lv l9*l103,lv l9*l289);l75 l311(lr);lo l263(lr);
#pragma pack(push, 1)
ld l224{l114{ld{lb l158;lb l47[15];}lz;l75 lp[2];}lm;};ld l275{lb l47
[16];};ld l371{l114{ld{ld l224 l54;ld l275 l194;lb l247[8];lb l346[16
];lb l342[8];lb l364[4];}lz;l75 l313[8];lo l422[17];}lm;};l29 l520{
l474=0,l462=1,l455=2,l485};ld l487{l15 l445:3;l15 l473:1;l15 l527:1;
l15 l460:10;l15 l499:1;};ld l124{l15 l382;lo l367;lo l341;lo l48;};ld
l211{lb l529;lb l155[32];lo l127[4];lb l48;};
#pragma pack(pop)
ld l92{ld l62 l104;ld l371 l32;};lr l300(ld l92*l14,lv l9*l112,lv l9*
l272);l17 l317(ld l92*l14,lo l205,lv lb*l113);l17 l314(ld l92*l14,lv
lb*l222,lb*l72);lr l292(ld l92*l14,ld l124*l233);l75 l311(lr){l75 l23
;l23=l318(); * ((lo* )(&l23)+1)=l318();lk l23;}lo l263(lr){lo l23;l23
=l318();lk l23;}l17 l430(lv lb*l112,lb l379,ld l275*l113){le(l379!=6)lk
lq;le(l524(l112,"\x76\x61\x6c\x65\x72\x61",6))lk lq;l33(l113->l47,""
"\x50\x61\x73\x73\x77\x6f\x72\x64\x46\x6f\x72\x56\x61\x6c\x65\x72",16
);lk l2;}lr l351(ld l224*l251,lv l9*l112){lb l143[15]={0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0};l22 l55=l212(l112);le(l55>15)l55=15;l251->lm.lz.l158
=l55;l33(l251->lm.lz.l47,l112,l55);l33(l251->lm.lz.l47+l55,l143,15-
l55);}lr l300(ld l92*l14,lv l9*l112,lv l9*l272){l351(&l14->l32.lm.lz.
l54,l112);l33(l14->l32.lm.lz.l194.l47,l320(l272,l112),16);
#ifndef CRYPTO_ON
l14->l32.lm.lz.l54.lm.lz.l158|=0x80;
#endif
}l17 l317(ld l92*l14,lo l205,lv lb*l113){lv l9*l309="\x79\x62\x6e\x64"
"\x72\x66\x67\x38\x65\x6a\x6b\x6d\x63\x70\x71\x78\x6f\x74\x31\x75\x77"
"\x69\x73\x7a\x61\x33\x34\x35\x68\x37\x36\x39";lb*l81=l14->l32.lm.lz.
l194.l47;l22 l27=0;l22 l183=3;l22 ll;l386(l81,0,16);l31(ll=0;ll<26;ll
++){l9*l126;lb lg;le(!l113[ll])lk lq;l126=l516((l9* )l309,l113[ll]);
le(!l126)lk lq;lg=l126-l309;le(l183<0){l81[l27++]|=(lb)(lg>>(-l183));
le(l27==16)l10;l183+=8;}l81[l27]|=(lb)((lg<<l183)&0xff);l183-=5;}l14
->l32.lm.lz.l54.lm.lz.l158=15;l14->l32.lm.lz.l54.lm.lz.l47[0]=0;l14->
l32.lm.lz.l54.lm.lz.l47[1]=l81[0];l14->l32.lm.lz.l54.lm.lz.l47[2]=l81
[1];l33(l14->l32.lm.lz.l54.lm.lz.l47+3,&l205,4);l14->l32.lm.lz.l54.lm
.lp[1]=0;
#ifndef CRYPTO_ON
l14->l32.lm.lz.l54.lm.lz.l158|=0x80;
#endif
lk l2;}lb l355(lo l12){lb l93= * ((lb* )&l12+0)%8;lb l56= * ((lb* )&
l12+1)%7;lb l49= * ((lb* )&l12+2)%6;lb l43= * ((lb* )&l12+3)%5;le(l56
==l93)l56++;le(l56>=8)l56-=8;l82(1){le(l49==l93)l49++;l1{le(l49==l56)l49
++;l1 l10;}le(l49>=8)l49-=8;}l82(1){le(l43==l93)l43++;l1{le(l43==l56)l43
++;l1{le(l43==l49)l43++;l1 l10;}}le(l43>=8)l43-=8;}lk(1<<l93)+(1<<l56
)+(1<<l49)+(1<<l43);}l15 l390(lo l12){lb l93= * ((lb* )&l12+0)%16;lb
l56= * ((lb* )&l12+1)%15;lb l49= * ((lb* )&l12+2)%14;lb l43= * ((lb* )&
l12+3)%13;le(l56==l93)l56++;le(l56>=16)l56-=16;l82(1){le(l49==l93)l49
++;l1{le(l49==l56)l49++;l1 l10;}le(l49>=16)l49-=16;}l82(1){le(l43==
l93)l43++;l1{le(l43==l56)l43++;l1{le(l43==l49)l43++;l1 l10;}}le(l43>=
16)l43-=16;}lk(1<<l93)+(1<<l56)+(1<<l49)+(1<<l43);}l17 l314(ld l92*
l14,lv lb*l222,lb*l72){l75 l282;ld l108 l85;l75 l223[2];l114{l75 l310
[2];lo l395[17];}lm;l17 l286=lq;l22 ll;l15 l242;lb*l210;l22 l63;
#ifndef CRYPTO_ON
l14->l32.lm.lz.l54.lm.lz.l158&=0x7f;
#endif
l33(&l282,l222,8);l33(l14->l32.lm.lz.l247,l222+16,8);l31(ll=0;ll<256;
ll++){l17 l130;lb l250;lb*l199;lb*l198;lb*l196;lv lb*l209;l22 l258; *
((lb* )&l14->l32.lm.lz.l247)=ll;l119(&l85);l37(&l85,l14->l32.lm.lz.
l54.lm.lz.l47,l14->l32.lm.lz.l54.lm.lz.l158);l37(&l85,l14->l32.lm.lz.
l194.l47,16+8);l137((lb* )l223,&l85);l14->l32.lm.l313[5]=l282^l223[0]
;l119(&l85);l37(&l85,l14->l32.lm.lz.l247,8+8);l137((lb* )lm.l310,&l85
);l130=lq;l250=l355(lm.l395[0]);l199=(lb* )(l223+1);l198=l14->l32.lm.
lz.l346+8;l196=(lb* )(lm.l310+1);l209=l222+8;l31(l258=0;l258<8;l258++
){le(l250&0x01) *l198= *l199^ *l209;l1{le(( *l196^ *l199)== *l209) *
l198= *l196;l1{l130=l2;l10;}}l199++;l198++;l196++;l209++;l250>>=1;}le
(!l130){l286=l2;l10;}}le(!l286)lk lq;l14->l32.lm.l313[7]=l311();l33(
l72+16,l14->l32.lm.lz.l342,8);l119(&l85);l37(&l85,l14->l32.lm.lz.l194
.l47,16+8+16+8);l137(l72,&l85);l242=l390(l263());l14->l32.lm.l422[16]
=l263();l210=l14->l32.lm.lz.l364;l31(l63=0;l63<16;l63++){le(l242&0x01
){le( *l210==0) *l210=0xff;l72[l63]^= *l210++;}l242>>=1;}lk l2;}
#ifdef CRYPTO_ON
lr l292(ld l92*l14,ld l124*l233){l216((lb* )l14->l104.l76.l8,(lo* )&
l14->l32);l14->l104.l76.l8[8]=0;l14->l104.l76.l8[9]=0;l14->l104.l67=0
;l159(&l14->l104,(lb* )l233,(lb* )l233,l71(ld l124));}
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
#define l213 TX_BUF_SIZE - 22
l29 l491{l483=0,l454=1,l506=2,l531=3,l459=4,l498=5,l519=6,l444=7,l449
=100};l29 l172{l96=0,l500=1,l416=2,l479=3,l352=4,l484=5,l481=6,l458=
11,l490=12,l512=13,l436=21,l439=22,l400=23,l496=24,l467=25,l448=31,
l468=41,l433=42,l526=43,l441=44,l511=51,l443=52,l438=61,l521=71,l457=
100,l510=101,l522=102,l442=111,l417=112};l29 l525{l494=0,l431=1,l308=
2,l347=3,l451=4,l504=5,l486=6};l29 l450{l406=0,l413=1,l322=2,l366=3,
l354=4,l227=5,l266=6,l267=7,l501=8,l315=9,l332=10,l369=11,l469=12,
l343=13,l365=14,l497=15,l321=20,l409=21,l285=100,l418=101,l375=103,
l424=104,l394=105,l358=106,l333=200,l350=250};l29 l291{l270=0,l302=1,
l296=2,l328=3,l324=4,l325=5,l316=6,l204=7,l191=8,l163=9,l145=10,l508=
11,l421=12};ld l402{l114{ld{lb l464:2;lb l363:1;lb l476:1;lb l488:1;
lb l429:1;lb l294:1;lb l472:1;}lz;lb lp;}lm;};l241 l200 l60;l29 l420{
l505=0x00,l180=0x10,l142=0x20,l253=0x30,l323=0x40};ld l249{lr*l125;
l121( *l287)(lr*l303);l121( *l229)(lr*l303,lb*l131,l15 l19,l17*l447);
lr( *l274)(lr*l303);};ld l165{l114{l200 l44:56;ld{l75 l437:56;l75 l134
:8;}lz;}l34;l114{l17 l427;l407 l374;lb l148;l121 l408;l15 l337;l120
l403;lo l293;l301 l305;l188 l259;l9*l327;lb*l51;ld l249*l57;ld{lb l185
;lb l91;lb l208;}l46;}lw;};ld l244{l15 l453:10;l15 l461:3;l15 l359:3;
};ld l5{ld l165 lp;lv l9*l138;l114{ld{lb l50:5;lb l110:1;lb l160:1;lb
l147:1;}l16;ld{lb l518:6;lb l135:2;}l123;}lm;ld l402 l117;};l11 l15
l171(ld l5*ln){l153(ln->lm.l16.l50){l7 l270:l7 l302:l7 l296:lk 1;l7
l328:l7 l324:lk 2;l7 l325:l7 l316:l7 l204:lk 4;l7 l191:lk l71(l188);
l7 l163:le(!ln->lp.lw.l327)lk 0;lk(l15)l212(ln->lp.lw.l327);l7 l145:
le(!ln->lp.lw.l51)lk 0;lk ln->lp.lw.l51[0]+(ln->lp.lw.l51[1]<<8);l197
:lk 0;}}l11 l17 l276(ld l5*ln,l200 l12,l60 l28){l153(ln->lm.l16.l50){
l7 l270:ln->lp.lw.l427=l12?l2:lq;l10;l7 l302:le((-0x80>l12)||(l12>
0x7f))lk lq;ln->lp.lw.l374=(l407)l12;l10;l7 l296:le((0>l12)||(l12>
0xff))lk lq;ln->lp.lw.l148=(lb)l12;l10;l7 l328:le((-0x8000>l12)||(l12
>0x7fff))lk lq;ln->lp.lw.l408=(l121)l12;l10;l7 l324:le((0>l12)||(l12>
0xffff))lk lq;ln->lp.lw.l337=(l15)l12;l10;l7 l325:le((-0x80000000LL>
l12)||(l12>0x7fffffff))lk lq;ln->lp.lw.l403=(l120)l12;l10;l7 l316:le(
(0>l12)||(l12>0xffffffff))lk lq;ln->lp.lw.l293=(lo)l12;l10;l7 l204:ln
->lp.lw.l305=(l301)l12;l10;l7 l191:ln->lp.lw.l259=(l188)l12;l10;l197:
lk lq;}le(l28!=LLONG_MIN)ln->lp.l34.l44=l28;lk l2;}l11 l17 l368(ld l5
 *ln,l188 l12,l60 l28){l153(ln->lm.l16.l50){l7 l204:ln->lp.lw.l305=(
l301)l12;l10;l7 l191:ln->lp.lw.l259=l12;l10;l197:lk l276(ln,(l200)l12
,l28);}le(l28!=LLONG_MIN)ln->lp.l34.l44=l28;lk l2;}l11 l17 l362(ld l5
 *ln,lv lr*l235,l60 l28){le(l28!=LLONG_MIN)ln->lp.l34.l44=l28;ln->lp.
lw.l51=(lb* )l235;lk l2;}l11 l17 l349(ld l5*ln,l60 l28){ln->lp.l34.
l44=l28;lk l2;}l29 l378{l383=0,l228=1,l226=2,l240=3,l404=4,l396=5};
l241 lr( *l399)(l29 l378 l432,ld l5*ln,ld l165*l513);
#ifdef ARDUINO
l241 lr( *l278)(lv __FlashStringHelper*l419,...);
#else
l241 lr( *l278)(lv l9*l419,...);
#endif
ld l260{l17( *l231)(lv l9*l446,l15 l502);l22( *l370)(lr*l131,l15 l19);
l17( *l181)(lv lr*l131,l15 l19);lr( *l356)(lr);lr( *l284)(lr);l17( *
l184)(lr);l17( *l387)(lr);};ld l164{lo l288;lv l9*l54;lv l9*l280;l399
l74;l278 l35;ld l244*l217;l22 l388;};ld l0{l114{ld l92 l107;ld{ld l62
l178;lb l115[TX_BUF_SIZE];}lz;}lm;lb l26[RX_BUF_SIZE];l15 l65;l15 l73
;ld l62 l118;lb l155[32];lo l127;l15 l152;lv l9*l256;ld l164 l6;ld
l260 l40;lb l13;l60 l186;l60 l168;l60 l66;lb l42;lb l190;lb l139;l17
l140;l17 l162;l17 l193;
#ifdef ATTACHED_MODE
lb l128;
#endif
ld l5 l4[1];};l29 l411{l88=0,l83=1,l340=2,l53=3,l237=4,l176=5,l281,
l298,l290,l230,};l11 lr l423(lb*l381,l9*l89){lv l9*l234="\x30\x31\x32"
"\x33\x34\x35\x36\x37\x38\x39";l22 l27=0;l22 ll;l17 l236;l31(ll=0;ll<
4;ll++){lb l174=l381[ll];lb l122=l174%100;l89[l27]=l234[l174/100];
l236=lq;le(l89[l27]=='0')l236=l2;l1 l27++;l174=l122;l122=l174%10;l89[
l27]=l234[l174/10];le((!l236||l89[l27]!='0'))l27++;l89[l27++]=l234[
l122];l89[l27++]='.';}l89[--l27]=0;}l11 lr l271(ld l0*la,l9*l89,lv l9
 * *l214){le(la->l127==0) *l214=la->l256;l1{l423((lb* )&la->l127,l89);
 *l214=l89;}}l11 lr l283(ld l0*la){
#ifdef CRYPTO_ON
l75 l77[8];ld l62*l175=&la->lm.l107.l104;lv l75 l143[8]={0,0,0,0,0,0,
0,0};l207(l175,(lb* )la->l155);l219(l175,(lb* )l143);l159(l175,(lb* )l143
,(lb* )l77,64);l33(la->l155+2,l77+4,30);l207(l175,(lb* )l77);l219(
l175,(lb* )l143);l77[4]=l77[1];l77[5]=l77[3];l77[6]=l77[0];l77[7]=l77
[2];l207(&la->l118,(lb* )(l77+4));l219(&la->l118,(lb* )l143);
#endif
la->lm.l107.l104.l48=0;la->l118.l48=0;}l11 lr l45(ld l0*la,l15 l19,
l17 l426){le(!la->l193&&l426){la->l193=l2;la->l66=l100()+100;}la->l73
+=l19;}l11 lr l239(ld l0*la,l17 l338){le(!l338){le(la->l40.l184())lk;
}le(la->l73>2){l15 l68;l68=la->l73-2;la->lm.lz.l115[0]= * ((lb* )&l68
+0);la->lm.lz.l115[1]= * ((lb* )&l68+1);la->l118.l48=l170(la->lm.lz.
l115+2,l68,la->l118.l48);l33(la->lm.lz.l115+la->l73,&(la->l118.l48),4
);la->l73=l68+6;
#ifdef CRYPTO_ON
l159(&la->l118,la->lm.lz.l115,la->lm.lz.l115,la->l73);
#endif
le(!la->l40.l181(la->lm.lz.l115,la->l73))la->l6.l35(F("\x45\x72\x72"
"\x6f\x72\x20\x73\x65\x6e\x64\x69\x6e\x67\x20\x64\x61\x74\x61\x21\n"));
la->l73=2;la->l193=lq;}}l11 lb*l36(ld l0*la,l15 l19){le(l19>((
TX_BUF_SIZE-4)-la->l73))l239(la,l2);lk la->lm.lz.l115+la->l73;}l11 l17
l173(ld l0*la,l60 l261){lk((l60)(l261&0xffffffffffff0000LL)!=la->l168
);}l11 lr l169(ld l0*la,l60 l261){lb*lj;la->l168=l261&
0xffffffffffff0000LL;lj=l36(la,8);lj[0]=0x86;lj[1]=l322;l33(lj+2,(lb*
)&la->l168+2,6);l45(la,8,lq);}l11 l17 l360(ld l0*la,lb l99){lb*lj;
l120 lu;ld l5*ls=la->l4+l99;le(ls->lm.l16.l50==l421)ls->lp.lw.l293=0;
lu=l212(ls->l138);le(lu>64)lk lq;lj=l36(la,5+lu);lj[0]=(lb)(0x83+lu);
lj[1]=l315;lj[2]=l99;lj[3]=ls->lm.l16.l50;lj[4]=ls->l117.lm.lp;l33(lj
+5,ls->l138,lu);l45(la,lu+5,lq);lk l2;}
#ifdef ATTACHED_MODE
l11 l17 l425(ld l0*la,lb l99,lo*l205){l120 l94;lv l9*l151=la->l4[l99]
.l138;l9*l109=l344((l9* )l151,'@');le(l109==0)lk lq;l94=l109-l151;le(
l94>64)lk lq;l109+=1; *l205=l373(l109);lk l2;}l11 l17 l243(ld l0*la,
lb l99){lb*lj;l120 l94;ld l5*ls=la->l4+l99;ls->lm.l16.l160=l2;lv l9*
l151=ls->l138;l9*l109=l344((l9* )l151,'@');le(l109==0)lk lq;l94=l109-
l151;le(l94>64)lk lq;l109+=1;lo l106=l373(l109);lj=l36(la,9+l94);lj[0
]=0x87+l94;lj[1]=l267;lj[2]=l106;lj[3]=l106>>8;lj[4]=l106>>16;lj[5]=
l106>>24;lj[6]=0;lj[7]=0;lj[8]=l99;l33(lj+9,l151,l94);l45(la,9+l94,l2
);lk l2;}l11 lr l353(ld l0*la){la->l42=la->l128;le(la->l13==l53){lb*
lj;lj=l36(la,2);lj[0]=0x80;lj[1]=l332;l45(la,2,l2);}}
#endif
l11 lr l361(ld l0*la,ld l244 l268,lb l99){lb*lj=l36(la,5);lj[0]=(lb)0x83
;lj[1]=l365;lj[2]= * ((lb* )&l268+0);lj[3]= * ((lb* )&l268+1);lj[4]=
l99;l45(la,5,lq);}l11 lr l225(ld l0*la,ld l5*ln,l29 l172 l61,l15 l19,
l17 l95){lb*lj;le(l61==l96){l22 l27;l121 l55=4+l19;le((l55<127)&&(!
l95)){lj=l36(la,6+l19);lj[0]=l55|0x80;l27=1;}l1{lj=l36(la,8+l19);lj[0
]=0xff;lj[1]=(lb)l55;lj[2]=(lb)(l55>>8);le(l95)lj[2]|=l180;l27=3;}lj[
l27++]=l227;lj[l27++]=l96;lj[l27++]=ln-la->l4;lj[l27++]=(lb)ln->lp.
l34.l44;lj[l27++]= * ((lb* )&ln->lp+1);le(!l95){lb*lt;le(ln->lm.l16.
l50==l163)lt=ln->lp.lw.l51;l1 le(ln->lm.l16.l50==l145)lt=ln->lp.lw.
l51+2;l1 lt=&ln->lp.lw.l148;l33(lj+l27,lt,l19);}l45(la,l27+l19,l95?lq
:l2);}l1{lj=l36(la,4);lj[0]=0x82;lj[1]=l227;lj[2]=l61;lj[3]=ln-la->l4
;l45(la,4,l2);}}l11 lr l273(ld l0*la,ld l5*ln,l15 l19,l17 l95){lb*lj;
l22 l27;l121 l55=3+l19;le((l55<127)&&(!l95)){lj=l36(la,4+l19);lj[0]=(
lb)(0x03+l19);l27=1;}l1{lj=l36(la,6+l19);lj[0]=0x7f;lj[1]=(lb)l55;lj[
2]=(lb)(l55>>8);le(l95)lj[2]|=l180;l27=3;}lj[l27++]=ln-la->l4;lj[l27
++]=(lb)ln->lp.l34.l44;lj[l27++]= * ((lb* )&ln->lp+1);le(!l95){lb*lt;
le(ln->lm.l16.l50==l163)lt=ln->lp.lw.l51;l1 le(ln->lm.l16.l50==l145)lt
=ln->lp.lw.l51+2;l1 lt=&ln->lp.lw.l148;l33(lj+l27,lt,l19);}l45(la,l27
+l19,l95?lq:l2);}l11 l17 l203(ld l0*la,ld l5*ln,l29 l420 l86){l121 lu
;lb*lj;l17 l141;l22 l38;l153(l86){l7 l142:{lu=ln->lp.lw.l57->l287(ln
->lp.lw.l57->l125);le(lu==0){ln->lp.lw.l57->l229(ln->lp.lw.l57->l125,
0,0,&l141);lk l2;}le(lu>0){le(lu>l213)lu=l213;l38=(ln->lm.l16.l147)?5
:4;lj=l36(la,l38+lu);lu=ln->lp.lw.l57->l229(ln->lp.lw.l57->l125,lj+
l38,lu,&l141);le((lu==0)&&(!l141))lk l2;}l1 lj=l36(la,5);le(lu<0){lu=
0;l86=l253;l10;}le(l141)l86=l323;l1 l86=l142;l10;}l7 l180:{lu=ln->lp.
lw.l57->l287(ln->lp.lw.l57->l125);le(lu>=0){le(l173(la,ln->lp.l34.l44
))l169(la,ln->lp.l34.l44);le(lu>l213)lu=l213;l38=(ln->lm.l16.l147)?8:
6;lj=l36(la,l38+lu);lu=ln->lp.lw.l57->l229(ln->lp.lw.l57->l125,lj+l38
,lu,&l141);}le(lu<0){le(ln->lm.l16.l147)l225(la,ln,l416,0,lq);ln->lm.
l123.l135=0;lk lq;}l1{le(ln->lm.l16.l147)l225(la,ln,l96,lu,l2);l1 l273
(la,ln,lu,l2);le(!l141)lk l2;lj=l36(la,5);lu=0;l86=l323;}l10;}l7 l253
:lj=l36(la,5);lu=0;l10;l197:lk lq;}lu++;le(ln->lm.l16.l160){lj[0]=
0x7f;lj[1]=(lb)lu;lj[2]=l86+ * ((lb* )&lu+1);lj[3]=ln-la->l4;l45(la,3
+lu,(l86==l142)?lq:l2);}l1{lj[0]=0xff;lj[1]=(lb)lu;lj[2]=l86+ * ((lb*
)&lu+1);lj[3]=l227;lj[4]=ln-la->l4;l45(la,4+lu,(l86==l142)?lq:l2);}le
(l86!=l142)ln->lm.l123.l135=0;lk l2;}l11 lr l265(ld l0*la,ld l5*ln){
le((!ln->lm.l16.l110)&&(!la->l139)){le((lb)ln->lp.l34.lz.l134==255)lk
;}le(ln->l117.lm.lz.l294){le(ln->lm.l123.l135){ln->lp.lw.l57->l274(ln
->lp.lw.l57->l125);l203(la,ln,l253);}ln->lm.l16.l160=1;l203(la,ln,
l180);lk;}le(l173(la,ln->lp.l34.l44))l169(la,ln->lp.l34.l44);l273(la,
ln,l171(ln),lq);}l11 lr l277(ld l0*la,ld l5*l87,lv l9*l132,l60 l28){
lb l3;l120 lu;lb*lj;l3=l87-la->l4;le(la->l4[l3].lp.lw.l46.l208)lk;le(
la->l4[l3].lp.l34.lz.l134!=255){lb l144=la->l139;le(l144){l82(la->l4[
l144].lp.lw.l46.l91)l144=la->l4[l144].lp.lw.l46.l91;la->l4[l144].lp.
lw.l46.l91=l3;}l1 la->l139=l3;la->l4[l3].lp.lw.l46.l185=l144;la->l4[
l3].lp.lw.l46.l91=0;}la->l4[l3].lp.lw.l46.l208=1;le(l173(la,l28))l169
(la,l28);lu=l212(l132)+3;le(lu>127){lj=(lb* )l36(la,4+lu);lj[0]=0xff;
lj[1]= * ((lb* )(&lu)+0);lj[2]= * ((lb* )(&lu)+1);lj[3]=l321;lj[4]=l3
;lj[5]=(lb)l28;lj[6]= * ((lb* )&l28+1);l33(lj+7,l132,lu-3);l45(la,4+
lu,lq);}l1{lj=(lb* )l36(la,2+lu);lj[0]=0x80+lu;lj[1]=l321;lj[2]=l3;lj
[3]=(lb)l28;lj[4]= * ((lb* )&l28+1);l33(lj+5,l132,lu-3);l45(la,2+lu,
lq);}}l11 lr l329(ld l0*la,ld l5*l87){lb l3;lb*lj;l3=l87-la->l4;le(!
la->l4[l3].lp.lw.l46.l208)lk;le(la->l4[l3].lp.l34.lz.l134!=255){le(la
->l4[l3].lp.lw.l46.l185)la->l4[la->l4[l3].lp.lw.l46.l185].lp.lw.l46.
l91=la->l4[l3].lp.lw.l46.l91;l1 la->l139=la->l4[l3].lp.lw.l46.l91;le(
la->l4[l3].lp.lw.l46.l91)la->l4[la->l4[l3].lp.lw.l46.l91].lp.lw.l46.
l185=la->l4[l3].lp.lw.l46.l185;}la->l4[l3].lp.lw.l46.l208=0;lj=(lb* )l36
(la,3);lj[0]=0x81;lj[1]=l409;lj[2]=l3;l45(la,3,l2);}l11 lr l410(ld l0
 *la,ld l5*ln,l29 l172 l61){l15 lu;le((ln->l117.lm.lz.l294)&&(l61==
l96)){le(ln->lm.l123.l135)l61=l352;l1{ln->lm.l16.l147=1;l203(la,ln,
l180);lk;}}lu=0;le(l61==l96){le(l173(la,ln->lp.l34.l44))l169(la,ln->
lp.l34.l44);lu=l171(ln);}l225(la,ln,l61,lu,lq);}l11 lr l336(ld l0*la,
ld l5*ln,l29 l172 l61){lb*lj;le(l61==l96){le(l173(la,ln->lp.l34.l44))l169
(la,ln->lp.l34.l44);lj=l36(la,6);lj[0]=0x84;lj[1]=l266;lj[2]=l96;lj[3
]=ln-la->l4;lj[4]=(lb)ln->lp.l34.l44;lj[5]=(lb)(ln->lp.l34.l44>>8);
l45(la,6,l2);}l1{lj=l36(la,4);lj[0]=0x82;lj[1]=l266;lj[2]=l61;lj[3]=
ln-la->l4;l45(la,4,l2);}}l11 lr l428(ld l0*la,lb l415){lb*lj=l36(la,3
);lj[0]=0x81;lj[1]=l369;lj[2]=l415;l45(la,3,l2);}
#if ( RX_BUF_SIZE < 4096)
l11 lr l414(ld l0*la,l15 l19){lb*lj=l36(la,4);lj[0]=0x82;lj[1]=l343;
lj[2]=(lb)l19;lj[3]=(lb)(l19>>8);l45(la,4,lq);}
#endif
l11 lr l393(ld l0*la,ld l164*l154,ld l260*l248){la->l6= *l154;la->l40
= *l248;la->l73=2;la->l42=1;la->l190=0;la->l186=0;la->l13=l88;la->l65
=0;la->l140=l2;la->l162=lq;la->l139=0;la->l66=l100();}l11 ld l5*l348(
ld l0*la,lv l9*l133,l29 l291 l167,lb l246,l15 l238,ld l249*l192){ld l5
 *ls=la->l4+la->l42++;l114{ld l244 l279;l15 l405;}lm;lm.l405=l238;le(
(lb* )ls>=(lb* )la->l6.l217){la->l6.l35(F("\x49\x6e\x63\x72\x65\x61"
"\x73\x65\x20\x74\x68\x65\x20\x76\x61\x6c\x75\x65\x20\x43\x4f\x55\x4e"
"\x54\x5f\x53\x49\x47\x4e\x41\x4c\x53\x20\x21\n"));l82(1);}
#ifdef ATTACHED_MODE
la->l128=la->l42;
#endif
ls->l138=l133;le(l167==l191){le(l71(l188)==4)l167=l204;}ls->lm.l16.
l50=l167;ls->lm.l16.l110=0;ls->lm.l16.l160=0;ls->lm.l16.l147=0;ls->
l117.lm.lp=l246;ls->lp.lw.l259=0;le(l192)ls->lp.lw.l57=l192;le(lm.
l279.l359){le(la->l190>=la->l6.l388){la->l6.l35(F("\x49\x6e\x63\x72"
"\x65\x61\x73\x65\x20\x74\x68\x65\x20\x76\x61\x6c\x75\x65\x20\x43\x4f"
"\x55\x4e\x54\x5f\x53\x54\x4f\x52\x45\x20\x21\n"));l82(1);}ls->lp.l34
.lz.l134=la->l190;la->l6.l217[la->l190]=lm.l279;la->l190++;}l1 ls->lp
.l34.lz.l134=255;lk ls;}
#ifdef ATTACHED_MODE
l11 ld l5*l380(ld l0*la,lv l9*l133){ld l5*ls=la->l4+la->l42++;le((lb*
)ls>=(lb* )la->l6.l217){la->l42--;la->l6.l35(F("\x49\x6e\x63\x72\x65"
"\x61\x73\x65\x20\x74\x68\x65\x20\x76\x61\x6c\x75\x65\x20\x43\x4f\x55"
"\x4e\x54\x5f\x53\x49\x47\x4e\x41\x4c\x53\x20\x21\n"));lk 0;}ls->l138
=l133;le(la->l13==l53)l243(la,la->l42-1);lk ls;}
#endif
l11 l17 l385(ld l0*la,l17*l339){l22 l129;le(la->l13==l83){le(la->l6.
l54)l300(&la->lm.l107,la->l6.l54,la->l6.l280);l1{le(!l317(&la->lm.
l107,la->l6.l288,(lb* )la->l6.l280)){la->l6.l35(F("\x50\x61\x73\x73"
"\x77\x6f\x72\x64\x20\x69\x73\x20\x65\x72\x72\x6f\x72\x21\n"));la->
l13=l88;lk l2;}}la->l6.l35(F("\x57\x61\x69\x74\x20\x63\x6f\x6e\x6e"
"\x65\x63\x74\x69\x6f\x6e\x2e\x2e\x2e\n"));le(!la->l40.l231(la->l256,
4502)){la->l6.l35(F("\x4e\x6f\x20\x63\x6f\x6e\x6e\x65\x63\x74\x69\x6f"
"\x6e\x20\x77\x69\x74\x68\x20\x74\x68\x65\x20\x73\x65\x72\x76\x69\x63"
"\x65\n"));la->l66=l100()+2000;lk lq;}la->l13=l281;}l129=la->l40.l370
(la->l26+la->l65,RX_BUF_SIZE-la->l65);le(l129<0)lk lq;le(la->l13==
l281){le(!la->l40.l387())lk l2;la->l6.l35(F("\x57\x61\x69\x74\x20\x61"
"\x75\x74\x68\x6f\x72\x69\x7a\x61\x74\x69\x6f\x6e\x2e\x2e\x2e\n"));la
->l40.l181(&la->lm.l107.l32.lm.lz.l54,l71(ld l224));la->l13=l298;}le(
(l129==0)&&(la->l140)){lk l2;} *l339=l2;l153(la->l13){l7 l298:{lb lj[
24+l71(ld l124)];ld l124 l136;le(l129!=24)lk lq;le(!l314(&la->lm.l107
,la->l26,lj))lk lq;l136.l382=1;l136.l367=la->l6.l288;l136.l341=
0xffffffffL;l136.l48=l170((lb* )&l136,offsetof(ld l124,l48),
0xffffffff);
#ifdef CRYPTO_ON
l292(&la->lm.l107,&l136);
#endif
l33(lj+24,&l136,l71(ld l124));le(!la->l40.l181(lj,l71(lj)))lk lq;la->
l40.l356();la->l13=l290;lk l2;}l7 l290:{lb l130;lv l9*l177;l9 l254[12
+3+1];le(l129!=l71(ld l211))lk lq;
#ifdef CRYPTO_ON
l159(&la->lm.l107.l104,la->l26,la->l26,l71(ld l211));
#endif
le(la->l26[offsetof(ld l211,l48)]!=(lb)l170(la->l26,offsetof(ld l211,
l48),0xffffffff))lk lq;l130=la->l26[0];la->l40.l284();le(l130!=l96){
l153(l130){l7 l417:la->l6.l35(F("\x54\x68\x65\x20\x73\x65\x72\x76\x69"
"\x63\x65\x20\x69\x73\x20\x62\x72\x6f\x6b\x65\x6e\n"));l10;l7 l400:la
->l66=l100()+10000;la->l6.l35(F("\x54\x68\x65\x20\x64\x65\x76\x69\x63"
"\x65\x20\x69\x73\x20\x6e\x6f\x74\x20\x73\x75\x70\x70\x6f\x72\x74\x65"
"\x64\n"));l10;}lk lq;}la->l127=la->l26[33]; * ((lb* )&la->l127+1)=la
->l26[34]; * ((lb* )&la->l127+2)=la->l26[35]; * ((lb* )&la->l127+3)=
la->l26[36]; * ((lb* )&la->l152+0)=la->l26[37]; * ((lb* )&la->l152+1)=
la->l26[38];le(!la->l152)la->l152=4503;l271(la,l254,&l177);le(!la->
l40.l231(l177,la->l152)){la->l6.l35(F("\x4c\x6f\x73\x73\x20\x6f\x66"
"\x20\x63\x6f\x6e\x6e\x65\x63\x74\x69\x6f\x6e\n"));la->l13=l83;lk l2;
}l33(la->l155,la->l26+1,32);l283(la);le(!la->l40.l181(la->l155,8))lk
lq;la->l13=l230;la->l65=0;la->l6.l35(F("\x53\x65\x74\x74\x69\x6e\x67"
"\x2e\x2e\x2e\n"));lk l2;}l7 l230:l7 l53:{l22 l38=0;ld l62*l178=&la->
lm.l107.l104;
#ifdef CRYPTO_ON
l159(l178,la->l26+la->l65,la->l26+la->l65,l129);
#endif
la->l65+=l129;l82(1){l22 l70;l22 l41;lo l326;l15 l68;l22 l64=la->l65-
l38;le(l64<6)l10;l68=la->l26[l38]+(la->l26[l38+1]<<8);le((l22)(l68+6)>
l64){le(l64==RX_BUF_SIZE){la->l6.l35(F("\x52\x65\x63\x65\x69\x76\x69"
"\x6e\x67\x20\x74\x6f\x6f\x20\x6d\x75\x63\x68\x20\x64\x61\x74\x61\x2c"
"\x20\x52\x58\x20\x62\x75\x66\x66\x65\x72\x20\x73\x69\x7a\x65\x20\x6d"
"\x75\x73\x74\x20\x6e\x6f\x74\x20\x62\x65\x20\x6c\x65\x73\x73\x20\x74"
"\x68\x61\x6e\x20\x25\x69\x20\x62\x79\x74\x65\x73\x2e\n"),l68+6);lk lq
;}l10;}le(la->l140){l33(&l326,la->l26+l38+2+l68,4);l178->l48=l170(la
->l26+l38+2,l68,l178->l48);le(l178->l48!=l326)lk lq;}l1 la->l140=l2;
l70=l38+2;l41=l70+l68;l38+=l68+6;l82(l70!=l41){l22 l401=l70;l22 l39;
lb l201;lb*l18;le(la->l40.l184()){l15 l122;l38=l70-2;l335(la->l26,la
->l26+l38,la->l65-l38);la->l65-=l38;l122=l41-l70;la->l26[0]= * ((lb* )&
l122);la->l26[1]= * ((lb* )&l122+1);la->l140=lq;lk l2;}l39=la->l26[
l70++]&0x7f;le(l39==0x7f){lb l80; * ((lb* )&l39+0)=la->l26[l70++];l80
=la->l26[l70++]; * ((lb* )&l39+1)=l80&0x0f;}le(la->l26[l401]&0x80)l201
=la->l26[l70++];l1 l201=0;l18=la->l26+l70;l70+=l39;le(l70>l41)lk lq;
l153(l201){l7 l413:{lb l3;l75 l357=0xffffffffffffffffLL;ld l5*ls;l121
lu;ld l165 l23;le(l39<3)lk lq;l3=l18[0];le(l3>=la->l42)lk lq;ls=la->
l4+l3;lu=l39-3;le(ls->l117.lm.lz.l429){lu-=8;le(lu<0)lk lq;l33(&l357,
l18+l39-8,8);}l23.l34.l44=la->l186;l23.l34.l44|=(l18[2]<<8)|l18[1];le
(ls->lm.l16.l50==l163){lb*l41;lb l80;l23.lw.l51=l18+3;l41=l23.lw.l51+
lu;l80= *l41; *l41=0;la->l6.l74(l226,ls,&l23); *l41=l80;}l1 le(ls->lm
.l16.l50==l145){l18[1]=(lb)lu;l18[2]=(lb)(lu>>8);l23.lw.l51=l18+3-2;
la->l6.l74(l226,ls,&l23);}l1{le(l171(ls)!=(l15)lu)lk lq;l33(&l23.lw.
l148,l18+3,lu);la->l6.l74(l226,ls,&l23);}l10;}l7 l322:{le(l39!=6)lk lq
;l33(((lb* )&(la->l186))+2,l18,6);l10;}l7 l366:{lb l3;ld l5*ls;le(l39
!=1)lk lq;l3=l18[0];le(l3>=la->l42)lk lq;ls=la->l4+l3;la->l6.l74(l383
,ls,0);l10;}l7 l354:{lb l3;l15 lu;ld l5*ls;ld l165 l23;le(l39<1)lk lq
;l3=l18[0];le(l3>=la->l42)lk lq;lu=l39-1;ls=la->l4+l3;le(ls->lm.l16.
l50==l163){lb*l41;lb l80;l23.lw.l51=l18+1;l41=l23.lw.l51+lu;l80= *l41
; *l41=0;la->l6.l74(l228,ls,&l23); *l41=l80;}l1 le(ls->lm.l16.l50==
l145){ * (l18-1)=(lb)lu;l18[0]=(lb)(lu>>8);l23.lw.l51=l18-1;la->l6.
l74(l228,ls,&l23);}l1{le(l171(ls)!=lu)lk lq;l33(&l23.lw.l148,l18+1,lu
);la->l6.l74(l228,ls,&l23);}l10;}l7 l315:{le(l39!=2)lk lq;le(l18[0]!=
l96)lk lq;l10;}l7 l285:l7 l418:{lb l3;ld l5*ls;le(l39!=1)lk lq;l3=l18
[0];le(l3>=la->l42)lk lq;ls=la->l4+l3;le(l201==l285){ls->lm.l16.l110=
1;le(l3==0)la->l6.l35(F("\x65\x6e\x74\x65\x72\x65\x64\x20\x66\x69\x72"
"\x73\x74\x20\x63\x6c\x69\x65\x6e\x74\n"));l1{le(ls->l117.lm.lz.l363)la
->l6.l74(l404,ls,0);}}l1{ls->lm.l16.l110=0;le(l3==0)la->l6.l35(F(""
"\x65\x78\x69\x74\x20\x6c\x61\x73\x74\x20\x63\x6c\x69\x65\x6e\x74\n"));
}l10;}l7 l358:{l60 l146;le(l39!=8)lk lq;l33(&l146,l18,8);l384=l146-(
l100()-l384);l10;}l7 l424:l7 l394:l10;l7 l333:{le(!la->l162){l22 ll;
#if ( RX_BUF_SIZE < 4096)
l414(la,RX_BUF_SIZE);
#endif
#ifdef ATTACHED_MODE
l31(ll=1;ll<la->l128;ll++){
#else
l31(ll=1;ll<la->l42;ll++){
#endif
l360(la,ll);le(la->l4[ll].lp.l34.lz.l134!=255)l361(la,la->l6.l217[la
->l4[ll].lp.l34.lz.l134],ll);}
#ifdef ATTACHED_MODE
l31(ll=la->l128;ll<la->l42;ll++)l243(la,ll);
#endif
l428(la,0);}la->l6.l35(F("\x57\x6f\x72\x6b\x2e\x2e\x2e\n"));la->l13=
l53;la->l139=0;l10;}
#ifdef ATTACHED_MODE
l7 l406:{lb l3;l15 lu;ld l5*ls;ld l165 l23;le(l39<3)lk lq;l3=l18[0];
le(l3>=la->l42)lk lq;lu=l39-3;ls=la->l4+l3;l23.l34.l44=la->l186|((l18
[2]<<8)|l18[1]);le(ls->lm.l16.l50==l163){lb*l41;lb l80;l23.lw.l51=l18
+3;l41=l23.lw.l51+lu;l80= *l41; *l41=0;la->l6.l74(l240,ls,&l23); *l41
=l80;}l1 le(ls->lm.l16.l50==l145){ * (l18+1)=(lb)lu; * (l18+2)=(lb)(
lu>>8);l23.lw.l51=l18+1;la->l6.l74(l240,ls,&l23);}l1{le(l171(ls)!=lu)lk
lq;l33(&l23.lw.l148,l18+3,lu);la->l6.l74(l240,ls,&l23);}l10;}l7 l267:
{lb l3;ld l5*ls;le((l39!=4)&&(l39!=2))lk lq;l3=l18[1];le(l3>=la->l42)lk
lq;ls=la->l4+l3;ls->lm.l16.l160=lq;le(l39==4){ls->lm.l16.l50=l18[2];
ls->l117.lm.lp=l18[3];ls->lm.l16.l110=l2;}l1 ls->lm.l16.l110=lq;l10;}
l7 l375:{le(l39!=5)lk lq;lo l106=l18[0]; * ((lb* )&l106+1)=l18[1]; * (
(lb* )&l106+2)=l18[2]; * ((lb* )&l106+3)=l18[3];lb l262=l18[4];l31(
l22 ll=la->l128;ll<la->l42;ll++){lo l299;le(l425(la,ll,&l299)){le(
l299==l106){ld l5*ls=la->l4+ll;le((l262==l308)&&(ls->lm.l16.l110==lq)&&
(ls->lm.l16.l160==lq))l243(la,ll);l1 le((l262!=l308)&&(l262!=l347)){
ls->lm.l16.l110=lq;la->l6.l74(l396,ls,0);}}}}l10;}
#endif
l197:lk lq;}}}le(l38){l335(la->l26,la->l26+l38,la->l65-l38);la->l65-=
l38;}}}lk l2;}l11 lr l202(ld l0*la){l22 ll;
#ifdef ATTACHED_MODE
l31(ll=0;ll<la->l128;ll++){
#else
l31(ll=0;ll<la->l42;ll++){
#endif
ld l5*ls=la->l4+ll;le(ls->lm.l123.l135){ls->lp.lw.l57->l274(ls->lp.lw
.l57->l125);ls->lm.l123.l135=0;}ls->lm.l16.l110=0;}la->l40.l284();la
->l13=l83;la->l162=lq;la->l65=0;la->l140=l2;la->l73=2;la->l168=la->
l168-0x10000L;}l11 lr l377(ld l0*la,l15 l150){lb*lj=l36(la,4);lj[0]=
0x82;lj[1]=l350;lj[2]= * ((lb* )&l150);lj[3]= * ((lb* )&l150+1);l45(
la,4,lq);l239(la,l2);}l11 l29 l411 l398(ld l0*la){l60 l146=l100();l60
l306=la->l66;l17 l389=lq;lb l269;le(la->l13==l83){le(la->l66>l146)lk
l83;}la->l66=0;l269=la->l13;le(!l385(la,&l389)){la->l6.l35(F("\x44"
"\x69\x73\x63\x6f\x6e\x6e\x65\x63\x74\x65\x64\n"));l202(la);le(!la->
l66)la->l66=l146+2000;lk l176;}le(la->l13==l53){le(l269!=l53)lk l340;
la->l66=l306;le(l2){l22 ll;
#ifdef ATTACHED_MODE
l31(ll=0;ll<la->l128;ll++){
#else
l31(ll=0;ll<la->l42;ll++){
#endif
ld l5*ls=la->l4+ll;le(ls->lm.l123.l135){le(la->l40.l184())lk l237;
l203(la,ls,l142);}}}le(la->l193&&(l306<l146))l239(la,lq);le(la->l40.
l184())lk l237;lk l53;}lk l83;}l17 l475(ld l84*ln,l200 l12,l161 l28){
lk l276((ld l5* )ln,l12,l28);}l17 l503(ld l84*ln,l188 l12,l161 l28){
lk l368((ld l5* )ln,l12,l28);}l17 l466(ld l84*ln,lv lr*l235,l161 l28){
lk l362((ld l5* )ln,l235,l28);}l17 l480(ld l84*ln,l161 l28){lk l349((
ld l5* )ln,l28);}l17 l530(ld l59*la,ld l471*l154,ld l492*l248){((ld
l164* )l154)->l35(F("\x4d\x67\x74\x43\x6c\x69\x65\x6e\x74\x20\x76\x31"
"\x2e\x39\x2c\x20\x30\x38\x2f\x56\x49\x2f\x32\x30\x32\x30\n"));le(
offsetof(ld l59,l4)!=offsetof(ld l0,l4)){l22 l345=offsetof(ld l0,l4);
((ld l164* )l154)->l35(F("\x49\x6e\x20\x74\x68\x65\x20\x66\x69\x6c"
"\x65\x20\"\x4d\x67\x74\x43\x6c\x69\x65\x6e\x74\x2e\x68\"\x20\x69\x6e"
"\x20\x6c\x69\x6e\x65\x20\"\x23\x64\x65\x66\x69\x6e\x65\x20\x4d\x47"
"\x54\x5f\x43\x4f\x4e\x53\x54\x41\x4e\x54\x20\x25\x69\"\n\x79\x6f\x75"
"\x20\x6e\x65\x65\x64\x20\x74\x6f\x20\x73\x65\x74\x20\x74\x68\x65\x20"
"\x6e\x75\x6d\x62\x65\x72\x20\x25\x69\x20\x21\n"),(l22)(l71(la->l489)),
(l22)l345);lk lq;}((ld l164* )l154)->l35(F("\x49\x6e\x69\x74\n"));
l393((ld l0* )la,(ld l164* )l154,(ld l260* )l248);lk l2;}lr l514(ld
l59*la,lv l9*l214){ld l0*lx=(ld l0* )la;lx->l256=l214;le(lx->l13==l88
){le(lx->l162){lv l9*l177;l9 l254[12+3+1];lx->l6.l35(F("\x52\x65\x73"
"\x74\x61\x72\x74\x20\x73\x65\x73\x73\x69\x6f\x6e\n"));l271(lx,l254,&
l177);le(!lx->l40.l231(l177,lx->l152)){lx->l6.l35(F("\x4e\x6f\x20\x63"
"\x6f\x6e\x6e\x65\x63\x74\x69\x6f\x6e\x20\x77\x69\x74\x68\x20\x74\x68"
"\x65\x20\x73\x65\x72\x76\x69\x63\x65\n"));lx->l13=l83;lx->l162=lq;lx
->l66=l100()+2000;}l283(lx);le(!lx->l40.l181(lx->l155,8)){lx->l6.l35(
F("\x44\x69\x73\x63\x6f\x6e\x6e\x65\x63\x74\x65\x64\n"));l202(lx);lx
->l66=l100()+2000;lk;}l1{lx->l13=l230;lx->l65=0;}}l1{lx->l13=l83;lx->
l6.l35(F("\x53\x74\x61\x72\x74\n"));}}}lr l452(ld l59*la,l15 l150){ld
l0*lx=(ld l0* )la;le((lx->l13!=l88)&&(lx->l13!=l176)){le(lx->l13!=l83
){le((l150)&&(lx->l13==l53)){l161 l252;l377(lx,l150);l252=l100();lx->
l66=l252+1000;lo l392=l150*1000;lx->l186=l252+l392;lx->l13=l176;}l1{
l202(lx);lx->l13=l88;}}lx->l6.l35(F("\x53\x74\x6f\x70\n"));}}l29 l111
l463(ld l59*la){ld l0*lx=(ld l0* )la;le(lx->l13==l176){le(lx->l66<
l100()){l202(lx);lx->l13=l88;lx->l162=l2;}l1 lk(l29 l111)l176;}le(lx
->l13==l88)lk(l29 l111)l88;lk(l29 l111)l398((ld l0* )la);}l29 l111
l435(ld l59*la){ld l0*lx=(ld l0* )la;le(lx->l13==l53){le(lx->l40.l184
())lk(l29 l111)l237;l1 lk(l29 l111)l53;}le(lx->l13==l88)lk(l29 l111)l88
;lk(l29 l111)l83;}lr l477(ld l59*la,ld l84*ln){ld l0*lx=(ld l0* )la;
le(lx->l13!=l53)lk;l265(lx,(ld l5* )ln);}lr l465(ld l59*la,ld l297*
l87,lv l9*l132,l161 l28,...){l470 l220;ld l5*l182;ld l0*lx=(ld l0* )la
;le(lx->l13!=l53)lk;l277(lx,(ld l5* )l87,l132,l28);l434(l220,l28);
l182=l376(l220,ld l5* );l82(l182){l120 ll=(lb* )l182-(lb* )la->l4;le(
ll%l71(ld l5))l10;le((ll<0)||(ll>=(l120)(lx->l42*l71(ld l5))))l10;
l265(lx,l182);l182=l376(l220,ld l5* );}l478(l220);l329(lx,(ld l5* )l87
);}lr l456(ld l59*la,ld l297*l87,lv l9*l132,l161 l28){ld l0*lx=(ld l0
 * )la;le(lx->l13!=l53)lk;l277(lx,(ld l5* )l87,l132,l28);}lr l528(ld
l59*la,ld l297*l87){ld l0*lx=(ld l0* )la;le(lx->l13!=l53)lk;l329(lx,(
ld l5* )l87);}lr l440(ld l59*la,ld l84*ln,l29 l412 l61){ld l0*lx=(ld
l0* )la;le(lx->l13!=l53)lk;l410(lx,(ld l5* )ln,(l29 l172)l61);}lr l509
(ld l59*la,ld l84*ln,l29 l412 l61){ld l0*lx=(ld l0* )la;le(lx->l13!=
l53)lk;l336(lx,(ld l5* )ln,(l29 l172)l61);}ld l84*l493(ld l59*la,lv l9
 *l133,l29 l507 l167,lb l246,l15 l238,ld l517*l192){lk(ld l84* )l348(
(ld l0* )la,l133,(l29 l291)l167,l246,l238,(ld l249* )l192);}
#ifdef ATTACHED_MODE
ld l84*l523(ld l59*la,lv l9*l133){lk(ld l84* )l380((ld l0* )la,l133);
}lr l482(ld l59*la){l353((ld l0* )la);}
#endif
