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
#define l12 static
#define le if
#define lk return
#define l32 memcpy
#define l78 while
#define l8 char
#define l225 unsigned
#define l21 int
#define l211 strlen
#define l516 strncmp
#define l31 for
#define l495 continue
#define l385 memset
#define l76 sizeof
#define l1 else
#define l171 crc32
#define l73 __uint64
#define l113 union
#define l29 enum
#define l14 __uint16
#define l16 bool
#define l316 rand
#define lq false
#define l429 memcmp
#define l2 true
#define l515 strchr
#define l11 break
#define l243 typedef
#define l202 __int64
#define l135 __int16
#define l228 read
#define l275 abort
#define l406 __int8
#define l125 __int32
#define l302 float
#define l189 double
#define l164 switch
#define l7 case
#define l195 default
#define l350 updateTime
#define l230 open
#define l298 close
#define l4 m_signals
#define l127 rem
#define l93 getUTCTime
#define ls signal
#define l343 strrchr
#define l372 atoi
#define l335 memmove
#define l147 time
#define l384 shiftTime
#define l475 signal_updateInt
#define l83 Signal
#define l163 TimeStamp
#define l503 signal_updateDouble
#define l465 signal_updatePtr
#define l480 signal_updateTime
#define l529 mgt_init
#define l59 MgtClient
#define l471 DeviceConfig
#define l492 PortableSocket
#define l490 m_reserv
#define l514 mgt_start
#define l454 mgt_stop
#define l112 MgtState
#define l463 mgt_run
#define l435 mgt_getState
#define l478 mgt_send
#define l464 mgt_eventSend
#define l295 Event
#define l469 va_list
#define l434 va_start
#define l374 va_arg
#define l477 va_end
#define l456 mgt_eventBegin
#define l527 mgt_eventEnd
#define l440 mgt_readAns
#define l411 ErrorCode
#define l509 mgt_writeAns
#define l493 mgt_createSignal
#define l507 SignalType
#define l517 ChunkedTransfer
#define l523 mgt_attachSignal
#define l482 mgt_detachAll


ld l95{lo l77[2];lo l30[4];lb l255[64];};lr l117(ld l95*ly);lr l38(ld
l95*ly,lv lb*l9,lo l60);lr l137(lb l50[16],ld l95*ly);lr l117(ld l95*
ly){ly->l77[0]=0;ly->l77[1]=0;ly->l30[0]=0x67452301;ly->l30[1]=
0xEFCDAB89;ly->l30[2]=0x98BADCFE;ly->l30[3]=0x10325476;}l12 lr l307(
ld l95*ly,lv lb lt[64]){lo lc[16],lh,lg,lf,li;{(lc[0])=((lo)(lt)[(0)]
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
lg;ly->l30[2]+=lf;ly->l30[3]+=li;}lr l38(ld l95*ly,lv lb*l9,lo l60){
lo l157,l167;le(!l60)lk;l157=ly->l77[0]&0x3F;l167=64-l157;ly->l77[0]
+=l60;ly->l77[0]&=0xFFFFFFFF;le(ly->l77[0]<l60)ly->l77[1]++;le(l157&&
l60>=l167){l32((lr* )(ly->l255+l157),(lr* )l9,l167);l307(ly,ly->l255);
l60-=l167;l9+=l167;l157=0;}l78(l60>=64){l307(ly,l9);l60-=64;l9+=64;}
le(l60)l32((lr* )(ly->l255+l157),(lr* )l9,l60);}l12 lb l392[64]={0x80
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};lr l137(lb
l50[16],ld l95*ly){lo l205,l311;lo l178,l186;lb l104[8];l178=(ly->l77
[0]>>29)|(ly->l77[1]<<3);l186=(ly->l77[0]<<3);{(l104)[(0)]=(lb)((l186
));(l104)[(0)+1]=(lb)((l186)>>8);(l104)[(0)+2]=(lb)((l186)>>16);(l104
)[(0)+3]=(lb)((l186)>>24);};{(l104)[(4)]=(lb)((l178));(l104)[(4)+1]=(
lb)((l178)>>8);(l104)[(4)+2]=(lb)((l178)>>16);(l104)[(4)+3]=(lb)((
l178)>>24);};l205=ly->l77[0]&0x3F;l311=(l205<56)?(56-l205):(120-l205);
l38(ly,l392,l311);l38(ly,l104,8);{(l50)[(0)]=(lb)((ly->l30[0]));(l50)[
(0)+1]=(lb)((ly->l30[0])>>8);(l50)[(0)+2]=(lb)((ly->l30[0])>>16);(l50
)[(0)+3]=(lb)((ly->l30[0])>>24);};{(l50)[(4)]=(lb)((ly->l30[1]));(l50
)[(4)+1]=(lb)((ly->l30[1])>>8);(l50)[(4)+2]=(lb)((ly->l30[1])>>16);(
l50)[(4)+3]=(lb)((ly->l30[1])>>24);};{(l50)[(8)]=(lb)((ly->l30[2]));(
l50)[(8)+1]=(lb)((ly->l30[2])>>8);(l50)[(8)+2]=(lb)((ly->l30[2])>>16);
(l50)[(8)+3]=(lb)((ly->l30[2])>>24);};{(l50)[(12)]=(lb)((ly->l30[3]));
(l50)[(12)+1]=(lb)((ly->l30[3])>>8);(l50)[(12)+2]=(lb)((ly->l30[3])>>
16);(l50)[(12)+3]=(lb)((ly->l30[3])>>24);};}lb*l318(lv l8*l96,lv l8*
l288){lv l8*l108, *l153;l12 lb l84[16];l225 l21 ll,l194,l103;ld l95 ly
,l70;l21 l179;l103=l211(l96);l108=l288;le(l516(l108,"\x24\x31\x24",3)==
0)l108+=3;l31(l153=l108; *l153!='\0'&& *l153!='$'&&l153<(l108+8);l153
++)l495;l194=l153-l108;l117(&ly);l38(&ly,(lv lb* )l96,l103);l38(&ly,(
lv lb* )"\x24\x31\x24",3);l38(&ly,(lv lb* )l108,l194);l117(&l70);l38(
&l70,(lv lb* )l96,l103);l38(&l70,(lv lb* )l108,l194);l38(&l70,(lv lb*
)l96,l103);l137(l84,&l70);l31(l179=l103;l179>0;l179-=16)l38(&ly,l84,(
l225 l21)(l179>16?16:l179));l385(l84,0,l76(l84));l31(ll=l103;ll!=0;ll
>>=1)le((ll&1)!=0)l38(&ly,l84,1);l1 l38(&ly,(lv lb* )l96,1);l137(l84,
&ly);l31(ll=0;ll<1000;ll++){l117(&l70);le((ll&1)!=0)l38(&l70,(lv lb* )l96
,l103);l1 l38(&l70,l84,16);le((ll%3)!=0)l38(&l70,(lv lb* )l108,l194);
le((ll%7)!=0)l38(&l70,(lv lb* )l96,l103);le((ll&1)!=0)l38(&l70,l84,16
);l1 l38(&l70,(lv lb* )l96,l103);l137(l84,&l70);}lk l84;}



#ifdef CRYPTO_ON
#define l20( l106, l245) (( lo)(( l106) + ( l245)))
#define l220( l106) ( l20(( l106),1))
ld l99{lo l9[16];};lr l197(lb l149[64],lv lo l9[16]);lr l397(ld l99*
lc,lv lb*l215,lb*lf,lo l81);lr l327(ld l99*lc,lv lb*l62);lr l330(ld
l99*lc,lv lb*l263);
#endif
#ifdef CRYPTO_ON
#define l24( l106, lf) ( ROTL32( l106, lf))
#define l25( l106, l245) (( l106) ^ ( l245))
#define l334( l131, l106) ((( lo  *  )( l131))[0] = l106)
#define l58( l131) ((( lo  *  )( l131))[0])
lr l197(lb l149[64],lv lo l9[16]){lo lc[16];l21 ll;l31(ll=0;ll<16;++
ll)lc[ll]=l9[ll];l31(ll=20;ll>0;ll-=2){lc[4]=l25(lc[4],l24(l20(lc[0],
lc[12]),7));lc[8]=l25(lc[8],l24(l20(lc[4],lc[0]),9));lc[12]=l25(lc[12
],l24(l20(lc[8],lc[4]),13));lc[0]=l25(lc[0],l24(l20(lc[12],lc[8]),18));
lc[9]=l25(lc[9],l24(l20(lc[5],lc[1]),7));lc[13]=l25(lc[13],l24(l20(lc
[9],lc[5]),9));lc[1]=l25(lc[1],l24(l20(lc[13],lc[9]),13));lc[5]=l25(
lc[5],l24(l20(lc[1],lc[13]),18));lc[14]=l25(lc[14],l24(l20(lc[10],lc[
6]),7));lc[2]=l25(lc[2],l24(l20(lc[14],lc[10]),9));lc[6]=l25(lc[6],
l24(l20(lc[2],lc[14]),13));lc[10]=l25(lc[10],l24(l20(lc[6],lc[2]),18));
lc[3]=l25(lc[3],l24(l20(lc[15],lc[11]),7));lc[7]=l25(lc[7],l24(l20(lc
[3],lc[15]),9));lc[11]=l25(lc[11],l24(l20(lc[7],lc[3]),13));lc[15]=
l25(lc[15],l24(l20(lc[11],lc[7]),18));lc[1]=l25(lc[1],l24(l20(lc[0],
lc[3]),7));lc[2]=l25(lc[2],l24(l20(lc[1],lc[0]),9));lc[3]=l25(lc[3],
l24(l20(lc[2],lc[1]),13));lc[0]=l25(lc[0],l24(l20(lc[3],lc[2]),18));
lc[6]=l25(lc[6],l24(l20(lc[5],lc[4]),7));lc[7]=l25(lc[7],l24(l20(lc[6
],lc[5]),9));lc[4]=l25(lc[4],l24(l20(lc[7],lc[6]),13));lc[5]=l25(lc[5
],l24(l20(lc[4],lc[7]),18));lc[11]=l25(lc[11],l24(l20(lc[10],lc[9]),7
));lc[8]=l25(lc[8],l24(l20(lc[11],lc[10]),9));lc[9]=l25(lc[9],l24(l20
(lc[8],lc[11]),13));lc[10]=l25(lc[10],l24(l20(lc[9],lc[8]),18));lc[12
]=l25(lc[12],l24(l20(lc[15],lc[14]),7));lc[13]=l25(lc[13],l24(l20(lc[
12],lc[15]),9));lc[14]=l25(lc[14],l24(l20(lc[13],lc[12]),13));lc[15]=
l25(lc[15],l24(l20(lc[14],lc[13]),18));}l31(ll=0;ll<16;++ll)lc[ll]=
l20(lc[ll],l9[ll]);l31(ll=0;ll<16;++ll)l334(l149+4*ll,lc[ll]);}l12 lv
l8*l217="\x65\x78\x70\x61\x6e\x64\x20\x33\x32\x2d\x62\x79\x74\x65\x20"
"\x6b";lr l327(ld l99*lc,lv lb*l62){lc->l9[1]=l58(l62+0);lc->l9[2]=
l58(l62+4);lc->l9[3]=l58(l62+8);lc->l9[4]=l58(l62+12);lc->l9[11]=l58(
l62+16);lc->l9[12]=l58(l62+20);lc->l9[13]=l58(l62+24);lc->l9[14]=l58(
l62+28);lc->l9[0]=l58(l217+0);lc->l9[5]=l58(l217+4);lc->l9[10]=l58(
l217+8);lc->l9[15]=l58(l217+12);}lr l330(ld l99*lc,lv lb*l263){lc->l9
[6]=l58(l263+0);lc->l9[7]=l58(l263+4);lc->l9[8]=0;lc->l9[9]=0;}lr l397
(ld l99*lc,lv lb*l215,lb*lf,lo l81){lb l149[64];l225 l21 ll;le(!l81)lk
;l31(;;){l197(l149,lc->l9);lc->l9[8]=l220(lc->l9[8]);le(!lc->l9[8]){
lc->l9[9]=l220(lc->l9[9]);}le(l81<=64){l31(ll=0;ll<l81;++ll)lf[ll]=
l215[ll]^l149[ll];lk;}l31(ll=0;ll<64;++ll)lf[ll]=l215[ll]^l149[ll];
l81-=64;lf+=64;l215+=64;}}
#endif
#ifdef CRYPTO_ON
ld l64{lb l47[64];lo l48;lb l68;ld l99 l74;};lr l373(ld l64*l19,ld l99
 *l317);lr l204(ld l64*l19,lv lb*l114);lr l214(ld l64*l19,lv lb*l293);
lr l159(ld l64*l19,lv lb*l124,lb*l72,lo l22);
#else
ld l64{lo l48;};
#endif
lo l171(lb*l133,lo l319,lo l79);
#ifdef CRYPTO_ON
lr l373(ld l64*l19,ld l99*l317){l19->l74= *l317;l19->l68=0;l19->l48=0
;}lr l204(ld l64*l19,lv lb*l114){l327(&l19->l74,l114);}lr l214(ld l64
 *l19,lv lb*l293){l330(&l19->l74,l293);l19->l68=0;l19->l48=0;}lr l159
(ld l64*l19,lv lb*l124,lb*l72,lo l22){l225 l21 ll;le(l19->l68){lb*lt=
l19->l47+64-l19->l68;le(l22>=l19->l68){l22-=l19->l68;l31(ll=0;ll<l19
->l68;++ll)l72[ll]=l124[ll]^lt[ll];l124+=l19->l68;l72+=l19->l68;l19->
l68=0;}l1{l19->l68-=l22;l31(ll=0;ll<l22;++ll)l72[ll]=l124[ll]^lt[ll];
l22=0;}}le(!l22)lk;l31(;;){l197((lb* )l19->l47,l19->l74.l9);l19->l74.
l9[8]=l220(l19->l74.l9[8]);le(!l19->l74.l9[8])l19->l74.l9[9]=l220(l19
->l74.l9[9]);le(l22<=64){l31(ll=0;ll<l22;++ll)l72[ll]=l124[ll]^l19->
l47[ll];l19->l68=64-l22;lk;}l31(ll=0;ll<64;++ll)l72[ll]=l124[ll]^l19
->l47[ll];l22-=64;l124+=64;l72+=64;}}
#endif
l12
#ifdef ARDUINO
__flash
#endif
lv lo l254[256]={0x00000000,0x77073096,0xee0e612c,0x990951ba,
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
l171(lb*l133,lo l319,lo l79){l78(l319--)
#ifdef ARDUINO
#ifdef pgm_read_dword_far
l79=pgm_read_dword_far(l254+((l79^ *l133++)&0xff))^(l79>>8);
#else
l79=pgm_read_dword(l254+((l79^ *l133++)&0xff))^(l79>>8);
#endif
#else
l79=l254[(l79^ *l133++)&0xff]^(l79>>8);
#endif
lk l79^0xffffffff;}
lb*l318(lv l8*l96,lv l8*l288);l73 l309(lr);lo l253(lr);
#pragma pack(push, 1)
ld l224{l113{ld{lb l158;lb l47[15];}lz;l73 lp[2];}lm;};ld l274{lb l47
[16];};ld l371{l113{ld{ld l224 l53;ld l274 l193;lb l247[8];lb l345[16
];lb l341[8];lb l364[4];}lz;l73 l312[8];lo l422[17];}lm;};l29 l520{
l474=0,l462=1,l455=2,l485};ld l487{l14 l445:3;l14 l473:1;l14 l526:1;
l14 l460:10;l14 l498:1;};ld l119{l14 l382;lo l367;lo l358;lo l48;};ld
l210{lb l528;lb l156[32];lo l128[4];lb l48;};
#pragma pack(pop)
ld l91{ld l64 l102;ld l371 l33;};lr l300(ld l91*l15,lv l8*l111,lv l8*
l271);l16 l305(ld l91*l15,lo l203,lv lb*l114);l16 l313(ld l91*l15,lv
lb*l209,lb*l72);lr l291(ld l91*l15,ld l119*l233);l73 l309(lr){l73 l23
;l23=l316(); * ((lo* )(&l23)+1)=l316();lk l23;}lo l253(lr){lo l23;l23
=l316();lk l23;}l16 l430(lv lb*l111,lb l378,ld l274*l114){le(l378!=6)lk
lq;le(l429(l111,"\x76\x61\x6c\x65\x72\x61",6))lk lq;l32(l114->l47,""
"\x50\x61\x73\x73\x77\x6f\x72\x64\x46\x6f\x72\x56\x61\x6c\x65\x72",16
);lk l2;}lr l349(ld l224*l251,lv l8*l111){lb l145[15]={0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0};l21 l56=l211(l111);le(l56>15)l56=15;l251->lm.lz.l158
=l56;l32(l251->lm.lz.l47,l111,l56);l32(l251->lm.lz.l47+l56,l145,15-
l56);}lr l300(ld l91*l15,lv l8*l111,lv l8*l271){l349(&l15->l33.lm.lz.
l53,l111);l32(l15->l33.lm.lz.l193.l47,l318(l271,l111),16);
#ifndef CRYPTO_ON
l15->l33.lm.lz.l53.lm.lz.l158|=0x80;
#endif
}l16 l305(ld l91*l15,lo l203,lv lb*l114){lv l8*l308="\x79\x62\x6e\x64"
"\x72\x66\x67\x38\x65\x6a\x6b\x6d\x63\x70\x71\x78\x6f\x74\x31\x75\x77"
"\x69\x73\x7a\x61\x33\x34\x35\x68\x37\x36\x39";lb*l81=l15->l33.lm.lz.
l193.l47;l21 l27=0;l21 l184=3;l21 ll;l385(l81,0,16);l31(ll=0;ll<26;ll
++){l8*l131;lb lg;le(!l114[ll])lk lq;l131=l515((l8* )l308,l114[ll]);
le(!l131)lk lq;lg=l131-l308;le(l184<0){l81[l27++]|=(lb)(lg>>(-l184));
le(l27==16)l11;l184+=8;}l81[l27]|=(lb)((lg<<l184)&0xff);l184-=5;}l15
->l33.lm.lz.l53.lm.lz.l158=15;l15->l33.lm.lz.l53.lm.lz.l47[0]=0;l15->
l33.lm.lz.l53.lm.lz.l47[1]=l81[0];l15->l33.lm.lz.l53.lm.lz.l47[2]=l81
[1];l32(l15->l33.lm.lz.l53.lm.lz.l47+3,&l203,4);l15->l33.lm.lz.l53.lm
.lp[1]=0;
#ifndef CRYPTO_ON
l15->l33.lm.lz.l53.lm.lz.l158|=0x80;
#endif
lk l2;}lb l354(lo l10){lb l105= * ((lb* )&l10+0)%8;lb l55= * ((lb* )&
l10+1)%7;lb l51= * ((lb* )&l10+2)%6;lb l42= * ((lb* )&l10+3)%5;le(l55
==l105)l55++;le(l55>=8)l55-=8;l78(1){le(l51==l105)l51++;l1{le(l51==
l55)l51++;l1 l11;}le(l51>=8)l51-=8;}l78(1){le(l42==l105)l42++;l1{le(
l42==l55)l42++;l1{le(l42==l51)l42++;l1 l11;}}le(l42>=8)l42-=8;}lk(1<<
l105)+(1<<l55)+(1<<l51)+(1<<l42);}l14 l390(lo l10){lb l105= * ((lb* )&
l10+0)%16;lb l55= * ((lb* )&l10+1)%15;lb l51= * ((lb* )&l10+2)%14;lb
l42= * ((lb* )&l10+3)%13;le(l55==l105)l55++;le(l55>=16)l55-=16;l78(1){
le(l51==l105)l51++;l1{le(l51==l55)l51++;l1 l11;}le(l51>=16)l51-=16;}
l78(1){le(l42==l105)l42++;l1{le(l42==l55)l42++;l1{le(l42==l51)l42++;
l1 l11;}}le(l42>=16)l42-=16;}lk(1<<l105)+(1<<l55)+(1<<l51)+(1<<l42);}
l16 l313(ld l91*l15,lv lb*l209,lb*l72){l73 l281;ld l95 l90;l73 l240[2
];l113{l73 l310[2];lo l395[17];}lm;l16 l284=lq;l21 ll;l14 l244;lb*
l208;l21 l62;
#ifndef CRYPTO_ON
l15->l33.lm.lz.l53.lm.lz.l158&=0x7f;
#endif
l32(&l281,l209,8);l32(l15->l33.lm.lz.l247,l209+16,8);l31(ll=0;ll<256;
ll++){l16 l132;lb l249;lb*l198;lb*l196;lb*l221;lv lb*l222;l21 l257; *
((lb* )&l15->l33.lm.lz.l247)=ll;l117(&l90);l38(&l90,l15->l33.lm.lz.
l53.lm.lz.l47,l15->l33.lm.lz.l53.lm.lz.l158);l38(&l90,l15->l33.lm.lz.
l193.l47,16+8);l137((lb* )l240,&l90);l15->l33.lm.l312[5]=l281^l240[0]
;l117(&l90);l38(&l90,l15->l33.lm.lz.l247,8+8);l137((lb* )lm.l310,&l90
);l132=lq;l249=l354(lm.l395[0]);l198=(lb* )(l240+1);l196=l15->l33.lm.
lz.l345+8;l221=(lb* )(lm.l310+1);l222=l209+8;l31(l257=0;l257<8;l257++
){le(l249&0x01) *l196= *l198^ *l222;l1{le(( *l221^ *l198)== *l222) *
l196= *l221;l1{l132=l2;l11;}}l198++;l196++;l221++;l222++;l249>>=1;}le
(!l132){l284=l2;l11;}}le(!l284)lk lq;l15->l33.lm.l312[7]=l309();l32(
l72+16,l15->l33.lm.lz.l341,8);l117(&l90);l38(&l90,l15->l33.lm.lz.l193
.l47,16+8+16+8);l137(l72,&l90);l244=l390(l253());l15->l33.lm.l422[16]
=l253();l208=l15->l33.lm.lz.l364;l31(l62=0;l62<16;l62++){le(l244&0x01
){le( *l208==0) *l208=0xff;l72[l62]^= *l208++;}l244>>=1;}lk l2;}
#ifdef CRYPTO_ON
lr l291(ld l91*l15,ld l119*l233){l197((lb* )l15->l102.l74.l9,(lo* )&
l15->l33);l15->l102.l74.l9[8]=0;l15->l102.l74.l9[9]=0;l15->l102.l68=0
;l159(&l15->l102,(lb* )l233,(lb* )l233,l76(ld l119));}
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
l29 l491{l483=0,l453=1,l506=2,l530=3,l459=4,l497=5,l519=6,l444=7,l449
=100};l29 l187{l109=0,l499=1,l415=2,l479=3,l351=4,l484=5,l481=6,l458=
11,l489=12,l512=13,l436=21,l439=22,l399=23,l500=24,l466=25,l448=31,
l470=41,l433=42,l525=43,l441=44,l511=51,l443=52,l438=61,l521=71,l457=
100,l510=101,l522=102,l442=111,l416=112};l29 l524{l494=0,l431=1,l297=
2,l344=3,l451=4,l504=5,l486=6};l29 l450{l405=0,l413=1,l321=2,l365=3,
l353=4,l227=5,l286=6,l268=7,l501=8,l314=9,l333=10,l370=11,l468=12,
l342=13,l366=14,l496=15,l320=20,l408=21,l283=100,l418=101,l375=103,
l423=104,l394=105,l357=106,l332=200,l348=250};l29 l290{l270=0,l301=1,
l280=2,l329=3,l322=4,l324=5,l315=6,l212=7,l192=8,l160=9,l146=10,l508=
11,l420=12};ld l401{l113{ld{lb l467:2;lb l363:1;lb l476:1;lb l488:1;
lb l427:1;lb l292:1;lb l472:1;}lz;lb lp;}lm;};l243 l202 l63;l29 l419{
l505=0x00,l170=0x10,l142=0x20,l252=0x30,l323=0x40};ld l248{lr*l121;
l135( *l285)(lr*l304);l135( *l228)(lr*l304,lb*l133,l14 l22,l16*l447);
lr( *l275)(lr*l304);};ld l165{l113{l202 l41:56;ld{l73 l437:56;l73 l122
:8;}lz;}l34;l113{l16 l426;l406 l376;lb l138;l135 l407;l14 l337;l125
l402;lo l296;l302 l303;l189 l256;l8*l326;lb*l52;ld l248*l57;ld{lb l168
;lb l92;lb l206;}l45;}lw;};ld l234{l14 l452:10;l14 l461:3;l14 l359:3;
};ld l5{ld l165 lp;lv l8*l141;l113{ld{lb l49:5;lb l98:1;lb l143:1;lb
l148:1;}l17;ld{lb l518:6;lb l136:2;}l123;}lm;ld l401 l116;};l12 l14
l190(ld l5*ln){l164(ln->lm.l17.l49){l7 l270:l7 l301:l7 l280:lk 1;l7
l329:l7 l322:lk 2;l7 l324:l7 l315:l7 l212:lk 4;l7 l192:lk l76(l189);
l7 l160:le(!ln->lp.lw.l326)lk 0;lk(l14)l211(ln->lp.lw.l326);l7 l146:
le(!ln->lp.lw.l52)lk 0;lk ln->lp.lw.l52[0]+(ln->lp.lw.l52[1]<<8);l195
:lk 0;}}l12 l16 l331(ld l5*ln,l202 l10,l63 l28){l164(ln->lm.l17.l49){
l7 l270:ln->lp.lw.l426=l10?l2:lq;l11;l7 l301:le((-0x80>l10)||(l10>
0x7f))lk lq;ln->lp.lw.l376=(l406)l10;l11;l7 l280:le((0>l10)||(l10>
0xff))lk lq;ln->lp.lw.l138=(lb)l10;l11;l7 l329:le((-0x8000>l10)||(l10
>0x7fff))lk lq;ln->lp.lw.l407=(l135)l10;l11;l7 l322:le((0>l10)||(l10>
0xffff))lk lq;ln->lp.lw.l337=(l14)l10;l11;l7 l324:le((-0x80000000LL>
l10)||(l10>0x7fffffff))lk lq;ln->lp.lw.l402=(l125)l10;l11;l7 l315:le(
(0>l10)||(l10>0xffffffff))lk lq;ln->lp.lw.l296=(lo)l10;l11;l7 l212:ln
->lp.lw.l303=(l302)l10;l11;l7 l192:ln->lp.lw.l256=(l189)l10;l11;l195:
lk lq;}le(l28!=LLONG_MIN)ln->lp.l34.l41=l28;lk l2;}l12 l16 l368(ld l5
 *ln,l189 l10,l63 l28){l164(ln->lm.l17.l49){l7 l212:ln->lp.lw.l303=(
l302)l10;l11;l7 l192:ln->lp.lw.l256=l10;l11;l195:lk l331(ln,(l202)l10
,l28);}le(l28!=LLONG_MIN)ln->lp.l34.l41=l28;lk l2;}l12 l16 l362(ld l5
 *ln,lv lr*l236,l63 l28){le(l28!=LLONG_MIN)ln->lp.l34.l41=l28;ln->lp.
lw.l52=(lb* )l236;lk l2;}l12 l16 l350(ld l5*ln,l63 l28){ln->lp.l34.
l41=l28;lk l2;}l29 l379{l383=0,l226=1,l231=2,l242=3,l403=4};l243 lr( *
l398)(l29 l379 l432,ld l5*ln,ld l165*l513);
#ifdef ARDUINO
l243 lr( *l277)(lv __FlashStringHelper*l417,...);
#else
l243 lr( *l277)(lv l8*l417,...);
#endif
ld l259{l16( *l230)(lv l8*l446,l14 l502);l21( *l369)(lr*l133,l14 l22);
l16( *l183)(lv lr*l133,l14 l22);lr( *l355)(lr);lr( *l298)(lr);l16( *
l185)(lr);l16( *l387)(lr);};ld l162{lo l287;lv l8*l53;lv l8*l279;l398
l82;l277 l35;ld l234*l216;l21 l388;};ld l0{l113{ld l91 l107;ld{ld l64
l177;lb l115[TX_BUF_SIZE];}lz;}lm;lb l26[RX_BUF_SIZE];l14 l66;l14 l71
;ld l64 l126;lb l156[32];lo l128;l14 l154;lv l8*l260;ld l162 l6;ld
l259 l40;lb l13;l63 l188;l63 l173;l63 l61;lb l44;lb l172;lb l150;l16
l139;l16 l161;l16 l207;
#ifdef ATTACHED_MODE
lb l130;
#endif
ld l5 l4[1];};l29 l410{l88=0,l86=1,l340=2,l54=3,l238=4,l180=5,l266,
l294,l289,l229,};l12 lr l421(lb*l381,l8*l87){lv l8*l235="\x30\x31\x32"
"\x33\x34\x35\x36\x37\x38\x39";l21 l27=0;l21 ll;l16 l237;l31(ll=0;ll<
4;ll++){lb l175=l381[ll];lb l127=l175%100;l87[l27]=l235[l175/100];
l237=lq;le(l87[l27]=='0')l237=l2;l1 l27++;l175=l127;l127=l175%10;l87[
l27]=l235[l175/10];le((!l237||l87[l27]!='0'))l27++;l87[l27++]=l235[
l127];l87[l27++]='.';}l87[--l27]=0;}l12 lr l272(ld l0*la,l8*l87,lv l8
 * *l219){le(la->l128==0) *l219=la->l260;l1{l421((lb* )&la->l128,l87);
 *l219=l87;}}l12 lr l282(ld l0*la){
#ifdef CRYPTO_ON
l73 l75[8];ld l64*l166=&la->lm.l107.l102;lv l73 l145[8]={0,0,0,0,0,0,
0,0};l204(l166,(lb* )la->l156);l214(l166,(lb* )l145);l159(l166,(lb* )l145
,(lb* )l75,64);l32(la->l156+2,l75+4,30);l204(l166,(lb* )l75);l214(
l166,(lb* )l145);l75[4]=l75[1];l75[5]=l75[3];l75[6]=l75[0];l75[7]=l75
[2];l204(&la->l126,(lb* )(l75+4));l214(&la->l126,(lb* )l145);
#endif
la->lm.l107.l102.l48=0;la->l126.l48=0;}l12 lr l46(ld l0*la,l14 l22,
l16 l425){le(!la->l207&&l425){la->l207=l2;la->l61=l93()+100;}la->l71
+=l22;}l12 lr l241(ld l0*la,l16 l338){le(!l338){le(la->l40.l185())lk;
}le(la->l71>2){l14 l67;l67=la->l71-2;la->lm.lz.l115[0]= * ((lb* )&l67
+0);la->lm.lz.l115[1]= * ((lb* )&l67+1);la->l126.l48=l171(la->lm.lz.
l115+2,l67,la->l126.l48);l32(la->lm.lz.l115+la->l71,&(la->l126.l48),4
);la->l71=l67+6;
#ifdef CRYPTO_ON
l159(&la->l126,la->lm.lz.l115,la->lm.lz.l115,la->l71);
#endif
le(!la->l40.l183(la->lm.lz.l115,la->l71))la->l6.l35(F("\x45\x72\x72"
"\x6f\x72\x20\x73\x65\x6e\x64\x69\x6e\x67\x20\x64\x61\x74\x61\x21\n"));
la->l71=2;la->l207=lq;}}l12 lb*l36(ld l0*la,l14 l22){le(l22>((
TX_BUF_SIZE-4)-la->l71))l241(la,l2);lk la->lm.lz.l115+la->l71;}l12 l16
l174(ld l0*la,l63 l261){lk((l63)(l261&0xffffffffffff0000LL)!=la->l173
);}l12 lr l181(ld l0*la,l63 l261){lb*lj;la->l173=l261&
0xffffffffffff0000LL;lj=l36(la,8);lj[0]=0x86;lj[1]=l321;l32(lj+2,(lb*
)&la->l173+2,6);l46(la,8,lq);}l12 l16 l360(ld l0*la,lb l100){lb*lj;
l125 lu;ld l5*ls=la->l4+l100;le(ls->lm.l17.l49==l420)ls->lp.lw.l296=0
;lu=l211(ls->l141);le(lu>64)lk lq;lj=l36(la,5+lu);lj[0]=(lb)(0x83+lu);
lj[1]=l314;lj[2]=l100;lj[3]=ls->lm.l17.l49;lj[4]=ls->l116.lm.lp;l32(
lj+5,ls->l141,lu);l46(la,lu+5,lq);lk l2;}
#ifdef ATTACHED_MODE
l12 l16 l424(ld l0*la,lb l100,lo*l203){l125 l101;lv l8*l152=la->l4[
l100].l141;l8*l110=l343((l8* )l152,'@');le(l110==0)lk lq;l101=l110-
l152;le(l101>64)lk lq;l110+=1; *l203=l372(l110);lk l2;}l12 l16 l264(
ld l0*la,lb l100){lb*lj;l125 l101;ld l5*ls=la->l4+l100;ls->lm.l17.
l143=l2;lv l8*l152=ls->l141;l8*l110=l343((l8* )l152,'@');le(l110==0)lk
lq;l101=l110-l152;le(l101>64)lk lq;l110+=1;lo l94=l372(l110);lj=l36(
la,9+l101);lj[0]=0x87+l101;lj[1]=l268;lj[2]=l94;lj[3]=l94>>8;lj[4]=
l94>>16;lj[5]=l94>>24;lj[6]=0;lj[7]=0;lj[8]=l100;l32(lj+9,l152,l101);
l46(la,9+l101,l2);lk l2;}l12 lr l352(ld l0*la){la->l44=la->l130;le(la
->l13==l54){lb*lj;lj=l36(la,2);lj[0]=0x80;lj[1]=l333;l46(la,2,l2);}}
#endif
l12 lr l361(ld l0*la,ld l234 l267,lb l100){lb*lj=l36(la,5);lj[0]=(lb)0x83
;lj[1]=l366;lj[2]= * ((lb* )&l267+0);lj[3]= * ((lb* )&l267+1);lj[4]=
l100;l46(la,5,lq);}l12 lr l232(ld l0*la,ld l5*ln,l29 l187 l65,l14 l22
,l16 l97){lb*lj;le(l65==l109){l21 l27;l135 l56=4+l22;le((l56<127)&&(!
l97)){lj=l36(la,6+l22);lj[0]=l56|0x80;l27=1;}l1{lj=l36(la,8+l22);lj[0
]=0xff;lj[1]=(lb)l56;lj[2]=(lb)(l56>>8);le(l97)lj[2]|=l170;l27=3;}lj[
l27++]=l227;lj[l27++]=l109;lj[l27++]=ln-la->l4;lj[l27++]=(lb)ln->lp.
l34.l41;lj[l27++]= * ((lb* )&ln->lp+1);le(!l97){lb*lt;le(ln->lm.l17.
l49==l160)lt=ln->lp.lw.l52;l1 le(ln->lm.l17.l49==l146)lt=ln->lp.lw.
l52+2;l1 lt=&ln->lp.lw.l138;l32(lj+l27,lt,l22);}l46(la,l27+l22,l97?lq
:l2);}l1{lj=l36(la,4);lj[0]=0x82;lj[1]=l227;lj[2]=l65;lj[3]=ln-la->l4
;l46(la,4,l2);}}l12 lr l273(ld l0*la,ld l5*ln,l14 l22,l16 l97){lb*lj;
l21 l27;l135 l56=3+l22;le((l56<127)&&(!l97)){lj=l36(la,4+l22);lj[0]=(
lb)(0x03+l22);l27=1;}l1{lj=l36(la,6+l22);lj[0]=0x7f;lj[1]=(lb)l56;lj[
2]=(lb)(l56>>8);le(l97)lj[2]|=l170;l27=3;}lj[l27++]=ln-la->l4;lj[l27
++]=(lb)ln->lp.l34.l41;lj[l27++]= * ((lb* )&ln->lp+1);le(!l97){lb*lt;
le(ln->lm.l17.l49==l160)lt=ln->lp.lw.l52;l1 le(ln->lm.l17.l49==l146)lt
=ln->lp.lw.l52+2;l1 lt=&ln->lp.lw.l138;l32(lj+l27,lt,l22);}l46(la,l27
+l22,l97?lq:l2);}l12 l16 l201(ld l0*la,ld l5*ln,l29 l419 l85){l135 lu
;lb*lj;l16 l140;l21 l37;l164(l85){l7 l142:{lu=ln->lp.lw.l57->l285(ln
->lp.lw.l57->l121);le(lu==0){ln->lp.lw.l57->l228(ln->lp.lw.l57->l121,
0,0,&l140);lk l2;}le(lu>0){le(lu>l213)lu=l213;l37=(ln->lm.l17.l148)?5
:4;lj=l36(la,l37+lu);lu=ln->lp.lw.l57->l228(ln->lp.lw.l57->l121,lj+
l37,lu,&l140);le((lu==0)&&(!l140))lk l2;}l1 lj=l36(la,5);le(lu<0){lu=
0;l85=l252;l11;}le(l140)l85=l323;l1 l85=l142;l11;}l7 l170:{lu=ln->lp.
lw.l57->l285(ln->lp.lw.l57->l121);le(lu>=0){le(l174(la,ln->lp.l34.l41
))l181(la,ln->lp.l34.l41);le(lu>l213)lu=l213;l37=(ln->lm.l17.l148)?8:
6;lj=l36(la,l37+lu);lu=ln->lp.lw.l57->l228(ln->lp.lw.l57->l121,lj+l37
,lu,&l140);}le(lu<0){le(ln->lm.l17.l148)l232(la,ln,l415,0,lq);ln->lm.
l123.l136=0;lk lq;}l1{le(ln->lm.l17.l148)l232(la,ln,l109,lu,l2);l1
l273(la,ln,lu,l2);le(!l140)lk l2;lj=l36(la,5);lu=0;l85=l323;}l11;}l7
l252:lj=l36(la,5);lu=0;l11;l195:lk lq;}lu++;le(ln->lm.l17.l143){lj[0]
=0x7f;lj[1]=(lb)lu;lj[2]=l85+ * ((lb* )&lu+1);lj[3]=ln-la->l4;l46(la,
3+lu,(l85==l142)?lq:l2);}l1{lj[0]=0xff;lj[1]=(lb)lu;lj[2]=l85+ * ((lb
 * )&lu+1);lj[3]=l227;lj[4]=ln-la->l4;l46(la,4+lu,(l85==l142)?lq:l2);
}le(l85!=l142)ln->lm.l123.l136=0;lk l2;}l12 lr l265(ld l0*la,ld l5*ln
){le((!ln->lm.l17.l98)&&(!la->l150)){le((lb)ln->lp.l34.lz.l122==255)lk
;}le(ln->l116.lm.lz.l292){le(ln->lm.l123.l136){ln->lp.lw.l57->l275(ln
->lp.lw.l57->l121);l201(la,ln,l252);}ln->lm.l17.l143=1;l201(la,ln,
l170);lk;}le(l174(la,ln->lp.l34.l41))l181(la,ln->lp.l34.l41);l273(la,
ln,l190(ln),lq);}l12 lr l276(ld l0*la,ld l5*l89,lv l8*l134,l63 l28){
lb l3;l125 lu;lb*lj;l3=l89-la->l4;le(la->l4[l3].lp.lw.l45.l206)lk;le(
la->l4[l3].lp.l34.lz.l122!=255){lb l151=la->l150;le(l151){l78(la->l4[
l151].lp.lw.l45.l92)l151=la->l4[l151].lp.lw.l45.l92;la->l4[l151].lp.
lw.l45.l92=l3;}l1 la->l150=l3;la->l4[l3].lp.lw.l45.l168=l151;la->l4[
l3].lp.lw.l45.l92=0;}la->l4[l3].lp.lw.l45.l206=1;le(l174(la,l28))l181
(la,l28);lu=l211(l134)+3;le(lu>127){lj=(lb* )l36(la,4+lu);lj[0]=0xff;
lj[1]= * ((lb* )(&lu)+0);lj[2]= * ((lb* )(&lu)+1);lj[3]=l320;lj[4]=l3
;lj[5]=(lb)l28;lj[6]= * ((lb* )&l28+1);l32(lj+7,l134,lu-3);l46(la,4+
lu,lq);}l1{lj=(lb* )l36(la,2+lu);lj[0]=0x80+lu;lj[1]=l320;lj[2]=l3;lj
[3]=(lb)l28;lj[4]= * ((lb* )&l28+1);l32(lj+5,l134,lu-3);l46(la,2+lu,
lq);}}l12 lr l328(ld l0*la,ld l5*l89){lb l3;lb*lj;l3=l89-la->l4;le(!
la->l4[l3].lp.lw.l45.l206)lk;le(la->l4[l3].lp.l34.lz.l122!=255){le(la
->l4[l3].lp.lw.l45.l168)la->l4[la->l4[l3].lp.lw.l45.l168].lp.lw.l45.
l92=la->l4[l3].lp.lw.l45.l92;l1 la->l150=la->l4[l3].lp.lw.l45.l92;le(
la->l4[l3].lp.lw.l45.l92)la->l4[la->l4[l3].lp.lw.l45.l92].lp.lw.l45.
l168=la->l4[l3].lp.lw.l45.l168;}la->l4[l3].lp.lw.l45.l206=0;lj=(lb* )l36
(la,3);lj[0]=0x81;lj[1]=l408;lj[2]=l3;l46(la,3,l2);}l12 lr l409(ld l0
 *la,ld l5*ln,l29 l187 l65){l14 lu;le((ln->l116.lm.lz.l292)&&(l65==
l109)){le(ln->lm.l123.l136)l65=l351;l1{ln->lm.l17.l148=1;l201(la,ln,
l170);lk;}}lu=0;le(l65==l109){le(l174(la,ln->lp.l34.l41))l181(la,ln->
lp.l34.l41);lu=l190(ln);}l232(la,ln,l65,lu,lq);}l12 lr l336(ld l0*la,
ld l5*ln,l29 l187 l65){lb*lj;le(l65==l109){le(l174(la,ln->lp.l34.l41))l181
(la,ln->lp.l34.l41);lj=l36(la,6);lj[0]=0x84;lj[1]=l286;lj[2]=l109;lj[
3]=ln-la->l4;lj[4]=(lb)ln->lp.l34.l41;lj[5]=(lb)(ln->lp.l34.l41>>8);
l46(la,6,l2);}l1{lj=l36(la,4);lj[0]=0x82;lj[1]=l286;lj[2]=l65;lj[3]=
ln-la->l4;l46(la,4,l2);}}l12 lr l428(ld l0*la,lb l414){lb*lj=l36(la,3
);lj[0]=0x81;lj[1]=l370;lj[2]=l414;l46(la,3,l2);}
#if ( RX_BUF_SIZE < 4096)
l12 lr l412(ld l0*la,l14 l22){lb*lj=l36(la,4);lj[0]=0x82;lj[1]=l342;
lj[2]=(lb)l22;lj[3]=(lb)(l22>>8);l46(la,4,lq);}
#endif
l12 lr l393(ld l0*la,ld l162*l155,ld l259*l223){la->l6= *l155;la->l40
= *l223;la->l71=2;la->l44=1;la->l172=0;la->l188=0;la->l13=l88;la->l66
=0;la->l139=l2;la->l161=lq;la->l150=0;la->l61=l93();}l12 ld l5*l347(
ld l0*la,lv l8*l129,l29 l290 l169,lb l246,l14 l239,ld l248*l191){ld l5
 *ls=la->l4+la->l44++;l113{ld l234 l278;l14 l404;}lm;lm.l404=l239;le(
(lb* )ls>=(lb* )la->l6.l216){la->l6.l35(F("\x49\x6e\x63\x72\x65\x61"
"\x73\x65\x20\x74\x68\x65\x20\x76\x61\x6c\x75\x65\x20\x43\x4f\x55\x4e"
"\x54\x5f\x53\x49\x47\x4e\x41\x4c\x53\x20\x21\n"));l78(1);}
#ifdef ATTACHED_MODE
la->l130=la->l44;
#endif
ls->l141=l129;le(l169==l192){le(l76(l189)==4)l169=l212;}ls->lm.l17.
l49=l169;ls->lm.l17.l98=0;ls->lm.l17.l143=0;ls->lm.l17.l148=0;ls->
l116.lm.lp=l246;ls->lp.lw.l256=0;le(l191)ls->lp.lw.l57=l191;le(lm.
l278.l359){le(la->l172>=la->l6.l388){la->l6.l35(F("\x49\x6e\x63\x72"
"\x65\x61\x73\x65\x20\x74\x68\x65\x20\x76\x61\x6c\x75\x65\x20\x43\x4f"
"\x55\x4e\x54\x5f\x53\x54\x4f\x52\x45\x20\x21\n"));l78(1);}ls->lp.l34
.lz.l122=la->l172;la->l6.l216[la->l172]=lm.l278;la->l172++;}l1 ls->lp
.l34.lz.l122=255;lk ls;}
#ifdef ATTACHED_MODE
l12 ld l5*l380(ld l0*la,lv l8*l129){ld l5*ls=la->l4+la->l44++;le((lb*
)ls>=(lb* )la->l6.l216){la->l44--;la->l6.l35(F("\x49\x6e\x63\x72\x65"
"\x61\x73\x65\x20\x74\x68\x65\x20\x76\x61\x6c\x75\x65\x20\x43\x4f\x55"
"\x4e\x54\x5f\x53\x49\x47\x4e\x41\x4c\x53\x20\x21\n"));lk 0;}ls->l141
=l129;le(la->l13==l54)l264(la,la->l44-1);lk ls;}
#endif
l12 l16 l386(ld l0*la,l16*l339){l21 l118;le(la->l13==l86){le(la->l6.
l53)l300(&la->lm.l107,la->l6.l53,la->l6.l279);l1{le(!l305(&la->lm.
l107,la->l6.l287,(lb* )la->l6.l279)){la->l6.l35(F("\x50\x61\x73\x73"
"\x77\x6f\x72\x64\x20\x69\x73\x20\x65\x72\x72\x6f\x72\x21\n"));la->
l13=l88;lk l2;}}la->l6.l35(F("\x57\x61\x69\x74\x20\x63\x6f\x6e\x6e"
"\x65\x63\x74\x69\x6f\x6e\x2e\x2e\x2e\n"));le(!la->l40.l230(la->l260,
4502)){la->l6.l35(F("\x4e\x6f\x20\x63\x6f\x6e\x6e\x65\x63\x74\x69\x6f"
"\x6e\x20\x77\x69\x74\x68\x20\x74\x68\x65\x20\x73\x65\x72\x76\x69\x63"
"\x65\n"));la->l61=l93()+2000;lk lq;}la->l13=l266;}l118=la->l40.l369(
la->l26+la->l66,RX_BUF_SIZE-la->l66);le(l118<0)lk lq;le(la->l13==l266
){le(!la->l40.l387())lk l2;la->l6.l35(F("\x57\x61\x69\x74\x20\x61\x75"
"\x74\x68\x6f\x72\x69\x7a\x61\x74\x69\x6f\x6e\x2e\x2e\x2e\n"));la->
l40.l183(&la->lm.l107.l33.lm.lz.l53,l76(ld l224));la->l13=l294;}le((
l118==0)&&(la->l139)){lk l2;} *l339=l2;l164(la->l13){l7 l294:{lb lj[
24+l76(ld l119)];ld l119 l120;le(l118!=24)lk lq;le(!l313(&la->lm.l107
,la->l26,lj))lk lq;l120.l382=1;l120.l367=la->l6.l287;l120.l358=
0xffffffffL;l120.l48=l171((lb* )&l120,offsetof(ld l119,l48),
0xffffffff);
#ifdef CRYPTO_ON
l291(&la->lm.l107,&l120);
#endif
l32(lj+24,&l120,l76(ld l119));le(!la->l40.l183(lj,l76(lj)))lk lq;la->
l40.l355();la->l13=l289;lk l2;}l7 l289:{lb l132;lv l8*l176;l8 l262[12
+3+1];le(l118!=l76(ld l210))lk lq;
#ifdef CRYPTO_ON
l159(&la->lm.l107.l102,la->l26,la->l26,l76(ld l210));
#endif
le(la->l26[offsetof(ld l210,l48)]!=(lb)l171(la->l26,offsetof(ld l210,
l48),0xffffffff))lk lq;l132=la->l26[0];la->l40.l298();le(l132!=l109){
l164(l132){l7 l416:la->l6.l35(F("\x54\x68\x65\x20\x73\x65\x72\x76\x69"
"\x63\x65\x20\x69\x73\x20\x62\x72\x6f\x6b\x65\x6e\n"));l11;l7 l399:la
->l61=l93()+10000;la->l6.l35(F("\x54\x68\x65\x20\x64\x65\x76\x69\x63"
"\x65\x20\x69\x73\x20\x6e\x6f\x74\x20\x73\x75\x70\x70\x6f\x72\x74\x65"
"\x64\n"));l11;}lk lq;}la->l128=la->l26[33]; * ((lb* )&la->l128+1)=la
->l26[34]; * ((lb* )&la->l128+2)=la->l26[35]; * ((lb* )&la->l128+3)=
la->l26[36]; * ((lb* )&la->l154+0)=la->l26[37]; * ((lb* )&la->l154+1)=
la->l26[38];le(!la->l154)la->l154=4503;l272(la,l262,&l176);le(!la->
l40.l230(l176,la->l154)){la->l6.l35(F("\x4c\x6f\x73\x73\x20\x6f\x66"
"\x20\x63\x6f\x6e\x6e\x65\x63\x74\x69\x6f\x6e\n"));la->l13=l86;lk l2;
}l32(la->l156,la->l26+1,32);l282(la);le(!la->l40.l183(la->l156,8))lk
lq;la->l13=l229;la->l66=0;la->l6.l35(F("\x53\x65\x74\x74\x69\x6e\x67"
"\x2e\x2e\x2e\n"));lk l2;}l7 l229:l7 l54:{l21 l37=0;ld l64*l177=&la->
lm.l107.l102;
#ifdef CRYPTO_ON
l159(l177,la->l26+la->l66,la->l26+la->l66,l118);
#endif
la->l66+=l118;l78(1){l21 l69;l21 l43;lo l325;l14 l67;l21 l60=la->l66-
l37;le(l60<6)l11;l67=la->l26[l37]+(la->l26[l37+1]<<8);le((l21)(l67+6)>
l60){le(l60==RX_BUF_SIZE){la->l6.l35(F("\x52\x65\x63\x65\x69\x76\x69"
"\x6e\x67\x20\x74\x6f\x6f\x20\x6d\x75\x63\x68\x20\x64\x61\x74\x61\x2c"
"\x20\x52\x58\x20\x62\x75\x66\x66\x65\x72\x20\x73\x69\x7a\x65\x20\x6d"
"\x75\x73\x74\x20\x6e\x6f\x74\x20\x62\x65\x20\x6c\x65\x73\x73\x20\x74"
"\x68\x61\x6e\x20\x25\x69\x20\x62\x79\x74\x65\x73\x2e\n"),l67+6);lk lq
;}l11;}le(la->l139){l32(&l325,la->l26+l37+2+l67,4);l177->l48=l171(la
->l26+l37+2,l67,l177->l48);le(l177->l48!=l325)lk lq;}l1 la->l139=l2;
l69=l37+2;l43=l69+l67;l37+=l67+6;l78(l69!=l43){l21 l400=l69;l21 l39;
lb l199;lb*l18;le(la->l40.l185()){l14 l127;l37=l69-2;l335(la->l26,la
->l26+l37,la->l66-l37);la->l66-=l37;l127=l43-l69;la->l26[0]= * ((lb* )&
l127);la->l26[1]= * ((lb* )&l127+1);la->l139=lq;lk l2;}l39=la->l26[
l69++]&0x7f;le(l39==0x7f){lb l80; * ((lb* )&l39+0)=la->l26[l69++];l80
=la->l26[l69++]; * ((lb* )&l39+1)=l80&0x0f;}le(la->l26[l400]&0x80)l199
=la->l26[l69++];l1 l199=0;l18=la->l26+l69;l69+=l39;le(l69>l43)lk lq;
l164(l199){l7 l413:{lb l3;l73 l356=0xffffffffffffffffLL;ld l5*ls;l135
lu;ld l165 l23;le(l39<3)lk lq;l3=l18[0];le(l3>=la->l44)lk lq;ls=la->
l4+l3;lu=l39-3;le(ls->l116.lm.lz.l427){lu-=8;le(lu<0)lk lq;l32(&l356,
l18+l39-8,8);}l23.l34.l41=la->l188;l23.l34.l41|=(l18[2]<<8)|l18[1];le
(ls->lm.l17.l49==l160){lb*l43;lb l80;l23.lw.l52=l18+3;l43=l23.lw.l52+
lu;l80= *l43; *l43=0;la->l6.l82(l231,ls,&l23); *l43=l80;}l1 le(ls->lm
.l17.l49==l146){l18[1]=(lb)lu;l18[2]=(lb)(lu>>8);l23.lw.l52=l18+3-2;
la->l6.l82(l231,ls,&l23);}l1{le(l190(ls)!=(l14)lu)lk lq;l32(&l23.lw.
l138,l18+3,lu);la->l6.l82(l231,ls,&l23);}l11;}l7 l321:{le(l39!=6)lk lq
;l32(((lb* )&(la->l188))+2,l18,6);l11;}l7 l365:{lb l3;ld l5*ls;le(l39
!=1)lk lq;l3=l18[0];le(l3>=la->l44)lk lq;ls=la->l4+l3;la->l6.l82(l383
,ls,0);l11;}l7 l353:{lb l3;l14 lu;ld l5*ls;ld l165 l23;le(l39<1)lk lq
;l3=l18[0];le(l3>=la->l44)lk lq;lu=l39-1;ls=la->l4+l3;le(ls->lm.l17.
l49==l160){lb*l43;lb l80;l23.lw.l52=l18+1;l43=l23.lw.l52+lu;l80= *l43
; *l43=0;la->l6.l82(l226,ls,&l23); *l43=l80;}l1 le(ls->lm.l17.l49==
l146){ * (l18-1)=(lb)lu;l18[0]=(lb)(lu>>8);l23.lw.l52=l18-1;la->l6.
l82(l226,ls,&l23);}l1{le(l190(ls)!=lu)lk lq;l32(&l23.lw.l138,l18+1,lu
);la->l6.l82(l226,ls,&l23);}l11;}l7 l314:{le(l39!=2)lk lq;le(l18[0]!=
l109)lk lq;l11;}l7 l283:l7 l418:{lb l3;ld l5*ls;le(l39!=1)lk lq;l3=
l18[0];le(l3>=la->l44)lk lq;ls=la->l4+l3;le(l199==l283){ls->lm.l17.
l98=1;le(l3==0)la->l6.l35(F("\x65\x6e\x74\x65\x72\x65\x64\x20\x66\x69"
"\x72\x73\x74\x20\x63\x6c\x69\x65\x6e\x74\n"));l1{le(ls->l116.lm.lz.
l363)la->l6.l82(l403,ls,0);}}l1{ls->lm.l17.l98=0;le(l3==0)la->l6.l35(
F("\x65\x78\x69\x74\x20\x6c\x61\x73\x74\x20\x63\x6c\x69\x65\x6e\x74"
"\n"));}l11;}l7 l357:{l63 l147;le(l39!=8)lk lq;l32(&l147,l18,8);l384=
l147-(l93()-l384);l11;}l7 l423:l7 l394:l11;l7 l332:{le(!la->l161){l21
ll;
#if ( RX_BUF_SIZE < 4096)
l412(la,RX_BUF_SIZE);
#endif
#ifdef ATTACHED_MODE
l31(ll=1;ll<la->l130;ll++){
#else
l31(ll=1;ll<la->l44;ll++){
#endif
l360(la,ll);le(la->l4[ll].lp.l34.lz.l122!=255)l361(la,la->l6.l216[la
->l4[ll].lp.l34.lz.l122],ll);}
#ifdef ATTACHED_MODE
l31(ll=la->l130;ll<la->l44;ll++)l264(la,ll);
#endif
l428(la,0);}la->l6.l35(F("\x57\x6f\x72\x6b\x2e\x2e\x2e\n"));la->l13=
l54;la->l150=0;l11;}
#ifdef ATTACHED_MODE
l7 l405:{lb l3;l14 lu;ld l5*ls;ld l165 l23;le(l39<3)lk lq;l3=l18[0];
le(l3>=la->l44)lk lq;lu=l39-3;ls=la->l4+l3;l23.l34.l41=la->l188|((l18
[2]<<8)|l18[1]);le(ls->lm.l17.l49==l160){lb*l43;lb l80;l23.lw.l52=l18
+3;l43=l23.lw.l52+lu;l80= *l43; *l43=0;la->l6.l82(l242,ls,&l23); *l43
=l80;}l1 le(ls->lm.l17.l49==l146){ * (l18+1)=(lb)lu; * (l18+2)=(lb)(
lu>>8);l23.lw.l52=l18+1;la->l6.l82(l242,ls,&l23);}l1{le(l190(ls)!=lu)lk
lq;l32(&l23.lw.l138,l18+3,lu);la->l6.l82(l242,ls,&l23);}l11;}l7 l268:
{lb l3;ld l5*ls;le((l39!=4)&&(l39!=2))lk lq;l3=l18[1];le(l3>=la->l44)lk
lq;ls=la->l4+l3;ls->lm.l17.l143=lq;le(l39==4){ls->lm.l17.l49=l18[2];
ls->l116.lm.lp=l18[3];ls->lm.l17.l98=l2;}l1 ls->lm.l17.l98=lq;l11;}l7
l375:{le(l39!=5)lk lq;lo l94=l18[0]; * ((lb* )&l94+1)=l18[1]; * ((lb*
)&l94+2)=l18[2]; * ((lb* )&l94+3)=l18[3];lb l258=l18[4];l31(l21 ll=la
->l130;ll<la->l44;ll++){lo l299;le(l424(la,ll,&l299)){le(l299==l94){
ld l5*ls=la->l4+ll;le((l258==l297)&&(ls->lm.l17.l98==lq)&&(ls->lm.l17
.l143==lq))l264(la,ll);l1 le((l258!=l297)&&(l258!=l344))ls->lm.l17.
l98=lq;}}}l11;}
#endif
l195:lk lq;}}}le(l37){l335(la->l26,la->l26+l37,la->l66-l37);la->l66-=
l37;}}}lk l2;}l12 lr l200(ld l0*la){l21 ll;
#ifdef ATTACHED_MODE
l31(ll=0;ll<la->l130;ll++){
#else
l31(ll=0;ll<la->l44;ll++){
#endif
ld l5*ls=la->l4+ll;le(ls->lm.l123.l136){ls->lp.lw.l57->l275(ls->lp.lw
.l57->l121);ls->lm.l123.l136=0;}ls->lm.l17.l98=0;}la->l40.l298();la->
l13=l86;la->l161=lq;la->l66=0;la->l139=l2;la->l71=2;la->l173=la->l173
-0x10000L;}l12 lr l377(ld l0*la,l14 l144){lb*lj=l36(la,4);lj[0]=0x82;
lj[1]=l348;lj[2]= * ((lb* )&l144);lj[3]= * ((lb* )&l144+1);l46(la,4,
lq);l241(la,l2);}l12 l29 l410 l396(ld l0*la){l63 l147=l93();l63 l306=
la->l61;l16 l389=lq;lb l269;le(la->l13==l86){le(la->l61>l147)lk l86;}
la->l61=0;l269=la->l13;le(!l386(la,&l389)){la->l6.l35(F("\x44\x69\x73"
"\x63\x6f\x6e\x6e\x65\x63\x74\x65\x64\n"));l200(la);le(!la->l61)la->
l61=l147+2000;lk l180;}le(la->l13==l54){le(l269!=l54)lk l340;la->l61=
l306;le(l2){l21 ll;
#ifdef ATTACHED_MODE
l31(ll=0;ll<la->l130;ll++){
#else
l31(ll=0;ll<la->l44;ll++){
#endif
ld l5*ls=la->l4+ll;le(ls->lm.l123.l136){le(la->l40.l185())lk l238;
l201(la,ls,l142);}}}le(la->l207&&(l306<l147))l241(la,lq);le(la->l40.
l185())lk l238;lk l54;}lk l86;}l16 l475(ld l83*ln,l202 l10,l163 l28){
lk l331((ld l5* )ln,l10,l28);}l16 l503(ld l83*ln,l189 l10,l163 l28){
lk l368((ld l5* )ln,l10,l28);}l16 l465(ld l83*ln,lv lr*l236,l163 l28){
lk l362((ld l5* )ln,l236,l28);}l16 l480(ld l83*ln,l163 l28){lk l350((
ld l5* )ln,l28);}l16 l529(ld l59*la,ld l471*l155,ld l492*l223){((ld
l162* )l155)->l35(F("\x4d\x67\x74\x43\x6c\x69\x65\x6e\x74\x20\x76\x31"
"\x2e\x39\x2c\x20\x30\x38\x2f\x56\x49\x2f\x32\x30\x32\x30\n"));le(
offsetof(ld l59,l4)!=offsetof(ld l0,l4)){l21 l346=offsetof(ld l0,l4);
((ld l162* )l155)->l35(F("\x49\x6e\x20\x74\x68\x65\x20\x66\x69\x6c"
"\x65\x20\"\x4d\x67\x74\x43\x6c\x69\x65\x6e\x74\x2e\x68\"\x20\x69\x6e"
"\x20\x6c\x69\x6e\x65\x20\"\x23\x64\x65\x66\x69\x6e\x65\x20\x4d\x47"
"\x54\x5f\x43\x4f\x4e\x53\x54\x41\x4e\x54\x20\x25\x69\"\n\x79\x6f\x75"
"\x20\x6e\x65\x65\x64\x20\x74\x6f\x20\x73\x65\x74\x20\x74\x68\x65\x20"
"\x6e\x75\x6d\x62\x65\x72\x20\x25\x69\x20\x21\n"),(l21)(l76(la->l490)),
(l21)l346);lk lq;}((ld l162* )l155)->l35(F("\x49\x6e\x69\x74\n"));
l393((ld l0* )la,(ld l162* )l155,(ld l259* )l223);lk l2;}lr l514(ld
l59*la,lv l8*l219){ld l0*lx=(ld l0* )la;lx->l260=l219;le(lx->l13==l88
){le(lx->l161){lv l8*l176;l8 l262[12+3+1];lx->l6.l35(F("\x52\x65\x73"
"\x74\x61\x72\x74\x20\x73\x65\x73\x73\x69\x6f\x6e\n"));l272(lx,l262,&
l176);le(!lx->l40.l230(l176,lx->l154)){lx->l6.l35(F("\x4e\x6f\x20\x63"
"\x6f\x6e\x6e\x65\x63\x74\x69\x6f\x6e\x20\x77\x69\x74\x68\x20\x74\x68"
"\x65\x20\x73\x65\x72\x76\x69\x63\x65\n"));lx->l13=l86;lx->l161=lq;lx
->l61=l93()+2000;}l282(lx);le(!lx->l40.l183(lx->l156,8)){lx->l6.l35(F
("\x44\x69\x73\x63\x6f\x6e\x6e\x65\x63\x74\x65\x64\n"));l200(lx);lx->
l61=l93()+2000;lk;}l1{lx->l13=l229;lx->l66=0;}}l1{lx->l13=l86;lx->l6.
l35(F("\x53\x74\x61\x72\x74\n"));}}}lr l454(ld l59*la,l14 l144){ld l0
 *lx=(ld l0* )la;le((lx->l13!=l88)&&(lx->l13!=l180)){le(lx->l13!=l86){
le((l144)&&(lx->l13==l54)){l163 l250;l377(lx,l144);l250=l93();lx->l61
=l250+1000;lo l391=l144*1000;lx->l188=l250+l391;lx->l13=l180;}l1{l200
(lx);lx->l13=l88;}}lx->l6.l35(F("\x53\x74\x6f\x70\n"));}}l29 l112 l463
(ld l59*la){ld l0*lx=(ld l0* )la;le(lx->l13==l180){le(lx->l61<l93()){
l200(lx);lx->l13=l88;lx->l161=l2;}l1 lk(l29 l112)l180;}le(lx->l13==
l88)lk(l29 l112)l88;lk(l29 l112)l396((ld l0* )la);}l29 l112 l435(ld
l59*la){ld l0*lx=(ld l0* )la;le(lx->l13==l54){le(lx->l40.l185())lk(
l29 l112)l238;l1 lk(l29 l112)l54;}le(lx->l13==l88)lk(l29 l112)l88;lk(
l29 l112)l86;}lr l478(ld l59*la,ld l83*ln){ld l0*lx=(ld l0* )la;le(lx
->l13!=l54)lk;l265(lx,(ld l5* )ln);}lr l464(ld l59*la,ld l295*l89,lv
l8*l134,l163 l28,...){l469 l218;ld l5*l182;ld l0*lx=(ld l0* )la;le(lx
->l13!=l54)lk;l276(lx,(ld l5* )l89,l134,l28);l434(l218,l28);l182=l374
(l218,ld l5* );l78(l182){l125 ll=(lb* )l182-(lb* )la->l4;le(ll%l76(ld
l5))l11;le((ll<0)||(ll>=(l125)(lx->l44*l76(ld l5))))l11;l265(lx,l182);
l182=l374(l218,ld l5* );}l477(l218);l328(lx,(ld l5* )l89);}lr l456(ld
l59*la,ld l295*l89,lv l8*l134,l163 l28){ld l0*lx=(ld l0* )la;le(lx->
l13!=l54)lk;l276(lx,(ld l5* )l89,l134,l28);}lr l527(ld l59*la,ld l295
 *l89){ld l0*lx=(ld l0* )la;le(lx->l13!=l54)lk;l328(lx,(ld l5* )l89);
}lr l440(ld l59*la,ld l83*ln,l29 l411 l65){ld l0*lx=(ld l0* )la;le(lx
->l13!=l54)lk;l409(lx,(ld l5* )ln,(l29 l187)l65);}lr l509(ld l59*la,
ld l83*ln,l29 l411 l65){ld l0*lx=(ld l0* )la;le(lx->l13!=l54)lk;l336(
lx,(ld l5* )ln,(l29 l187)l65);}ld l83*l493(ld l59*la,lv l8*l129,l29
l507 l169,lb l246,l14 l239,ld l517*l191){lk(ld l83* )l347((ld l0* )la
,l129,(l29 l290)l169,l246,l239,(ld l248* )l191);}
#ifdef ATTACHED_MODE
ld l83*l523(ld l59*la,lv l8*l129){lk(ld l83* )l380((ld l0* )la,l129);
}lr l482(ld l59*la){l352((ld l0* )la);}
#endif
