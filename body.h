#ifndef BODY_H
#define BODY_H

enum {
	BODY_HEAD,
	BODY_CHEST,
	BODY_TORSO,
	BODY_ARM,
	BODY_HAND,
	BODY_LEG,
	BODY_FOOT,
	BODY_HEART,
	BODY_LUNGS,
	BODY_STOMACH
};

struct body {
	const char *head;
	const char *chest;
	const char *torso;

	const char *arm;
	const char *hand;

	const char *leg;
	const char *foot;

	const char *heart;
	const char *lungs;
	const char *stomach;

	const char *reserved0;
	const char *reserved1;
	const char *reserved2;
	const char *reserved3;
	const char *reserved4;
	const char *reserved5;
	const char *reserved6;
	const char *reserved7;
	const char *reserved8;
	const char *reserved9;
	const char *reserved10;
	const char *reserved11;
	const char *reserved12;
	const char *reserved13;
	const char *reserved14;
	const char *reserved15;
};

#endif
