#pragma once
#include "Vec.h"

class playerent {
public:
	Vec3 CamCoords; //0x0004
	Vec3 Velocity1; //0x0010
	char pad_001C[24]; //0x001C
	Vec3 BodyCoords; //0x0034
	Vec2 ViewAngles; //0x0040
	char pad_0048[12]; //0x0048
	float AirTime; //0x0054
	char pad_0058[4]; //0x0058
	float BodyHeightCurrent; //0x005C
	float BodyHeightNormal; //0x0060
	float BodyWidthCurrent; //0x0064
	char pad_0068[1]; //0x0068
	bool onGround; //0x0069
	char pad_006A[6]; //0x006A
	int8_t IsIdle; //0x0070
	int8_t IsScooping; //0x0071
	char pad_0072[16]; //0x0072
	int8_t bState; //0x0082
	int8_t bVisibleMode; //0x0083
	char pad_0084[116]; //0x0084
	int32_t Health; //0x00F8
	int32_t Armor; //0x00FC
	int32_t primary; //0x0100
	int32_t nextPrimary; //0x0104
	char pad_0108[4]; //0x0108
	int32_t hasSpecial; //0x010C
	char pad_0110[36]; //0x0110
	int32_t SpecialReserveAmmo; //0x0134
	char pad_0138[32]; //0x0138
	int32_t GrenadeCount; //0x0158
	char pad_015C[160]; //0x015C
	int32_t frags; //0x01FC
	int32_t flags; //0x0200
	int32_t deaths; //0x0204
	int32_t points; //0x0208
	char pad_020C[24]; //0x020C
	int8_t isAttacking; //0x0224
	char username[16]; //0x0225
	char pad_0235[247]; //0x0235
	int8_t TeamId; //0x032C
	char pad_032D[11]; //0x032D
	int8_t bSpectMode; //0x0338
	char pad_0339[59]; //0x0339
	class WeaponClass* WeaponPtr; //0x0374
	char pad_0378[1292]; //0x0378

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x0884


class WeaponClass {
public:
	int32_t WeaponID; //0x0004
	class WeaponParent* ParentPtr; //0x0008
	class DataClass* DataPtr; //0x000C
	class ReserveAmmoClass* ReservePtr; //0x0010
	class ClipAmmoClass* ClipPtr; //0x0014
	class CooldownClass* CooldownPtr; //0x0018
	int32_t IsShooting; //0x001C
	int32_t IsReloading; //0x0020
	char pad_0024[32]; //0x0024

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x0044


class WeaponParent {
public:
	char pad_0000[68]; //0x0000
}; //Size: 0x0044


class DataClass {
public:
	char className[8]; //0x0000
	char pad_0008[252]; //0x0008
	int8_t shot_soundId; //0x0104
	int8_t N000002F3; //0x0105
	int8_t reload_soundId; //0x0106
	int8_t N000002F4; //0x0107
	int8_t N00000230; //0x0108
	int8_t N000002F6; //0x0109
	int8_t N00000313; //0x010A
	int8_t N000002F7; //0x010B
	int8_t bullet_damage; //0x010C
	int8_t bullet_multiplier; //0x010D
	int8_t N00000316; //0x010E
	int8_t N000002FA; //0x010F
	int8_t N00000232; //0x0110
	int8_t N000002FC; //0x0111
	int8_t N00000319; //0x0112
	int8_t N000002FD; //0x0113
	int8_t N00000233; //0x0114
	int8_t N000002FF; //0x0115
	int8_t N0000031C; //0x0116
	int8_t N00000300; //0x0117
	int8_t N00000234; //0x0118
	int8_t N00000302; //0x0119
	int8_t N0000031F; //0x011A
	int8_t N00000303; //0x011B
	int8_t N00000235; //0x011C
	int8_t N00000305; //0x011D
	int8_t N00000322; //0x011E
	int8_t N00000306; //0x011F
	int8_t recoily1; //0x0120
	int8_t N00000308; //0x0121
	int8_t recoily2; //0x0122
	int8_t N00000309; //0x0123
	int8_t N00000237; //0x0124
	int8_t N0000030B; //0x0125
	int8_t N00000328; //0x0126
	int8_t N0000030C; //0x0127
	int8_t N00000238; //0x0128
	int8_t isAuto; //0x0129
	char pad_012A[798]; //0x012A
}; //Size: 0x0448

class ReserveAmmoClass {
public:
	int32_t ReserveValue; //0x0000
	char pad_0004[64]; //0x0004
}; //Size: 0x0044

class ClipAmmoClass {
public:
	int32_t ClipValue; //0x0000
	char pad_0004[64]; //0x0004
}; //Size: 0x0044

class CooldownClass {
public:
	int32_t CurrentCooldown; //0x0000
	char pad_0004[64]; //0x0004
}; //Size: 0x0044


struct EntList {
	playerent* ents[31];
};

