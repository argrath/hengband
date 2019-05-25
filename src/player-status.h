﻿#pragma once 

/*
 * Most of the "player" information goes here.
 *
 * This stucture gives us a large collection of player variables.
 *
 * This structure contains several "blocks" of information.
 *   (1) the "permanent" info
 *   (2) the "variable" info
 *   (3) the "transient" info
 *
 * All of the "permanent" info, and most of the "variable" info,
 * is saved in the savefile.  The "transient" info is recomputed
 * whenever anything important changes.
 */

/*
 * Player constants
 */
#define PY_MAX_EXP      99999999L       /*!< プレイヤー経験値の最大値 / Maximum exp */
#define PY_MAX_GOLD     999999999L      /*!< プレイヤー所持金の最大値 / Maximum gold */
#define PY_MAX_LEVEL    50              /*!< プレイヤーレベルの最大値 / Maximum level */

extern const concptr stat_names[6];
extern const concptr stat_names_reduced[6];

typedef struct player_type player_type;

struct player_type
{
	POSITION oldpy;		/* Previous player location -KMW- */
	POSITION oldpx;		/* Previous player location -KMW- */

	SEX_IDX psex;		/* Sex index */
	RACE_IDX prace;		/* Race index */
	CLASS_IDX pclass;	/* Class index */
	CHARACTER_IDX pseikaku;	/* Seikaku index */
	REALM_IDX realm1;		/* First magic realm */
	REALM_IDX realm2;		/* Second magic realm */
	CHARACTER_IDX oops;		/* Unused */

	DICE_SID hitdie;	/* Hit dice (sides) */
	u16b expfact;	/* Experience factor
					* Note: was byte, causing overflow for Amberite
					* characters (such as Amberite Paladins)
					*/

	s16b age;			/* Characters age */
	s16b ht;			/* Height */
	s16b wt;			/* Weight */
	s16b sc;			/* Social Class */

	PRICE au;			/* Current Gold */

	EXP max_max_exp;	/* Max max experience (only to calculate score) */
	EXP max_exp;		/* Max experience */
	EXP exp;			/* Cur experience */
	u32b exp_frac;		/* Cur exp frac (times 2^16) */

	PLAYER_LEVEL lev;			/* Level */

	TOWN_IDX town_num;			/* Current town number */
	s16b arena_number;		/* monster number in arena -KMW- */
	bool inside_arena;		/* Is character inside arena? */
	QUEST_IDX inside_quest;		/* Inside quest level */
	bool inside_battle;		/* Is character inside tougijou? */

	DUNGEON_IDX dungeon_idx; /* current dungeon index */
	POSITION wilderness_x;	/* Coordinates in the wilderness */
	POSITION wilderness_y;
	bool wild_mode;

	HIT_POINT mhp;			/* Max hit pts */
	HIT_POINT chp;			/* Cur hit pts */
	u32b chp_frac;		/* Cur hit frac (times 2^16) */
	PERCENTAGE mutant_regenerate_mod;

	MANA_POINT msp;			/* Max mana pts */
	MANA_POINT csp;			/* Cur mana pts */
	u32b csp_frac;		/* Cur mana frac (times 2^16) */

	s16b max_plv;		/* Max Player Level */

	#define A_STR 0
	#define A_INT 1
	#define A_WIS 2
	#define A_DEX 3
	#define A_CON 4
	#define A_CHR 5
	#define A_MAX 6
	BASE_STATUS stat_max[6];	/* Current "maximal" stat values */
	BASE_STATUS stat_max_max[6];	/* Maximal "maximal" stat values */
	BASE_STATUS stat_cur[6];	/* Current "natural" stat values */

	s16b learned_spells;
	s16b add_spells;

	u32b count;

	TIME_EFFECT fast;		/* Timed -- Fast */
	TIME_EFFECT slow;		/* Timed -- Slow */
	TIME_EFFECT blind;		/* Timed -- Blindness */
	TIME_EFFECT paralyzed;		/* Timed -- Paralysis */
	TIME_EFFECT confused;		/* Timed -- Confusion */
	TIME_EFFECT afraid;		/* Timed -- Fear */
	TIME_EFFECT image;		/* Timed -- Hallucination */
	TIME_EFFECT poisoned;		/* Timed -- Poisoned */
	TIME_EFFECT cut;		/* Timed -- Cut */
	TIME_EFFECT stun;		/* Timed -- Stun */

	TIME_EFFECT protevil;		/* Timed -- Protection */
	TIME_EFFECT invuln;		/* Timed -- Invulnerable */
	TIME_EFFECT ult_res;		/* Timed -- Ultimate Resistance */
	TIME_EFFECT hero;		/* Timed -- Heroism */
	TIME_EFFECT shero;		/* Timed -- Super Heroism */
	TIME_EFFECT shield;		/* Timed -- Shield Spell */
	TIME_EFFECT blessed;		/* Timed -- Blessed */
	TIME_EFFECT tim_invis;		/* Timed -- See Invisible */
	TIME_EFFECT tim_infra;		/* Timed -- Infra Vision */
	TIME_EFFECT tsuyoshi;		/* Timed -- Tsuyoshi Special */
	TIME_EFFECT ele_attack;	/* Timed -- Elemental Attack */
	TIME_EFFECT ele_immune;	/* Timed -- Elemental Immune */

	TIME_EFFECT oppose_acid;	/* Timed -- oppose acid */
	TIME_EFFECT oppose_elec;	/* Timed -- oppose lightning */
	TIME_EFFECT oppose_fire;	/* Timed -- oppose heat */
	TIME_EFFECT oppose_cold;	/* Timed -- oppose cold */
	TIME_EFFECT oppose_pois;	/* Timed -- oppose poison */

	TIME_EFFECT tim_esp;       /* Timed ESP */
	TIME_EFFECT wraith_form;   /* Timed wraithform */

	TIME_EFFECT resist_magic;  /* Timed Resist Magic (later) */
	TIME_EFFECT tim_regen;
	TIME_EFFECT kabenuke;
	TIME_EFFECT tim_stealth;
	TIME_EFFECT tim_levitation;
	TIME_EFFECT tim_sh_touki;
	TIME_EFFECT lightspeed;
	TIME_EFFECT tsubureru;
	TIME_EFFECT magicdef;
	TIME_EFFECT tim_res_nether;	/* Timed -- Nether resistance */
	TIME_EFFECT tim_res_time;	/* Timed -- Time resistance */
	MIMIC_RACE_IDX mimic_form;
	TIME_EFFECT tim_mimic;
	TIME_EFFECT tim_sh_fire;
	TIME_EFFECT tim_sh_holy;
	TIME_EFFECT tim_eyeeye;

	/* for mirror master */
	TIME_EFFECT tim_reflect;       /* Timed -- Reflect */
	TIME_EFFECT multishadow;       /* Timed -- Multi-shadow */
	TIME_EFFECT dustrobe;          /* Timed -- Robe of dust */

	bool timewalk;
	GAME_TURN resting;	/* Current counter for resting, if any */

	PATRON_IDX chaos_patron;

	BIT_FLAGS muta1; /*!< レイシャル型の変異 / "Activatable" mutations must be in MUT1_* */
#define MUT1_SPIT_ACID                  0x00000001L /*!< 突然変異: 酸の唾 */
#define MUT1_BR_FIRE                    0x00000002L /*!< 突然変異: 炎のブレス */
#define MUT1_HYPN_GAZE                  0x00000004L /*!< 突然変異: 催眠睨み */
#define MUT1_TELEKINES                  0x00000008L /*!< 突然変異: 念動力 */
#define MUT1_VTELEPORT                  0x00000010L /*!< 突然変異: テレポート / Voluntary teleport */
#define MUT1_MIND_BLST                  0x00000020L /*!< 突然変異: 精神攻撃 */
#define MUT1_RADIATION                  0x00000040L /*!< 突然変異: 放射能 */
#define MUT1_VAMPIRISM                  0x00000080L /*!< 突然変異: 吸血 */
#define MUT1_SMELL_MET                  0x00000100L /*!< 突然変異: 金属嗅覚 */
#define MUT1_SMELL_MON                  0x00000200L /*!< 突然変異: 敵臭嗅覚 */
#define MUT1_BLINK                      0x00000400L /*!< 突然変異: ショート・テレポート */
#define MUT1_EAT_ROCK                   0x00000800L /*!< 突然変異: 岩喰い */
#define MUT1_SWAP_POS                   0x00001000L /*!< 突然変異: 位置交換 */
#define MUT1_SHRIEK                     0x00002000L /*!< 突然変異: 叫び */
#define MUT1_ILLUMINE                   0x00004000L /*!< 突然変異: 照明 */
#define MUT1_DET_CURSE                  0x00008000L /*!< 突然変異: 呪い感知 */
#define MUT1_BERSERK                    0x00010000L /*!< 突然変異: 狂戦士化 */
#define MUT1_POLYMORPH                  0x00020000L /*!< 突然変異: 変身 */
#define MUT1_MIDAS_TCH                  0x00040000L /*!< 突然変異: ミダスの手 */
#define MUT1_GROW_MOLD                  0x00080000L /*!< 突然変異: カビ発生 */
#define MUT1_RESIST                     0x00100000L /*!< 突然変異: エレメント耐性 */
#define MUT1_EARTHQUAKE                 0x00200000L /*!< 突然変異: 地震 */
#define MUT1_EAT_MAGIC                  0x00400000L /*!< 突然変異: 魔力喰い */
#define MUT1_WEIGH_MAG                  0x00800000L /*!< 突然変異: 魔力感知 */
#define MUT1_STERILITY                  0x01000000L /*!< 突然変異: 増殖阻止 */
#define MUT1_PANIC_HIT                  0x02000000L /*!< 突然変異: ヒットアンドアウェイ */
#define MUT1_DAZZLE                     0x04000000L /*!< 突然変異: 眩惑 */
#define MUT1_LASER_EYE                  0x08000000L /*!< 突然変異: レーザー・アイ */
#define MUT1_RECALL                     0x10000000L /*!< 突然変異: 帰還 */
#define MUT1_BANISH                     0x20000000L /*!< 突然変異: 邪悪消滅 */
#define MUT1_COLD_TOUCH                 0x40000000L /*!< 突然変異: 凍結の手 */
#define MUT1_LAUNCHER                   0x80000000L /*!< 突然変異: アイテム投げ */

	BIT_FLAGS muta2; /*!< 常時効果つきの変異1 / Randomly activating mutations must be MUT2_* */
#define MUT2_BERS_RAGE                  0x00000001L /*!< 突然変異: 狂戦士化の発作 */
#define MUT2_COWARDICE                  0x00000002L /*!< 突然変異: 臆病 */
#define MUT2_RTELEPORT                  0x00000004L /*!< 突然変異: ランダムテレポート / Random teleport, instability */
#define MUT2_ALCOHOL                    0x00000008L /*!< 突然変異: アルコール分泌 */
#define MUT2_HALLU                      0x00000010L /*!< 突然変異: 幻覚を引き起こす精神錯乱 */
#define MUT2_FLATULENT                  0x00000020L /*!< 突然変異: 猛烈な屁 */
#define MUT2_SCOR_TAIL                  0x00000040L /*!< 突然変異: サソリの尻尾 */
#define MUT2_HORNS                      0x00000080L /*!< 突然変異: ツノ */
#define MUT2_BEAK                       0x00000100L /*!< 突然変異: クチバシ */
#define MUT2_ATT_DEMON                  0x00000200L /*!< 突然変異: デーモンを引き付ける */
#define MUT2_PROD_MANA                  0x00000400L /*!< 突然変異: 制御できない魔力のエネルギー */
#define MUT2_SPEED_FLUX                 0x00000800L /*!< 突然変異: ランダムな加減速 */
#define MUT2_BANISH_ALL                 0x00001000L /*!< 突然変異: ランダムなモンスター消滅 */
#define MUT2_EAT_LIGHT                  0x00002000L /*!< 突然変異: 光源喰い */
#define MUT2_TRUNK                      0x00004000L /*!< 突然変異: 象の鼻 */
#define MUT2_ATT_ANIMAL                 0x00008000L /*!< 突然変異: 動物を引き寄せる */
#define MUT2_TENTACLES                  0x00010000L /*!< 突然変異: 邪悪な触手 */
#define MUT2_RAW_CHAOS                  0x00020000L /*!< 突然変異: 純カオス */
#define MUT2_NORMALITY                  0x00040000L /*!< 突然変異: ランダムな変異の消滅 */
#define MUT2_WRAITH                     0x00080000L /*!< 突然変異: ランダムな幽体化 */
#define MUT2_POLY_WOUND                 0x00100000L /*!< 突然変異: ランダムな傷の変化 */
#define MUT2_WASTING                    0x00200000L /*!< 突然変異: 衰弱 */
#define MUT2_ATT_DRAGON                 0x00400000L /*!< 突然変異: ドラゴンを引き寄せる */
#define MUT2_WEIRD_MIND                 0x00800000L /*!< 突然変異: ランダムなテレパシー */
#define MUT2_NAUSEA                     0x01000000L /*!< 突然変異: 落ち着きの無い胃 */
#define MUT2_CHAOS_GIFT                 0x02000000L /*!< 突然変異: カオスパトロン */
#define MUT2_WALK_SHAD                  0x04000000L /*!< 突然変異: ランダムな現実変容 */
#define MUT2_WARNING                    0x08000000L /*!< 突然変異: 警告 */
#define MUT2_INVULN                     0x10000000L /*!< 突然変異: ランダムな無敵化 */
#define MUT2_SP_TO_HP                   0x20000000L /*!< 突然変異: ランダムなMPからHPへの変換 */
#define MUT2_HP_TO_SP                   0x40000000L /*!< 突然変異: ランダムなHPからMPへの変換 */
#define MUT2_DISARM                     0x80000000L /*!< 突然変異: ランダムな武器落とし */

	BIT_FLAGS muta3; /*!< 常時効果つきの変異2 / Other mutations will be mainly in MUT3_* */
#define MUT3_HYPER_STR                  0x00000001L /*!< 突然変異: 超人的な力 */
#define MUT3_PUNY                       0x00000002L /*!< 突然変異: 虚弱 */
#define MUT3_HYPER_INT                  0x00000004L /*!< 突然変異: 生体コンピュータ */
#define MUT3_MORONIC                    0x00000008L /*!< 突然変異: 精神薄弱 */
#define MUT3_RESILIENT                  0x00000010L /*!< 突然変異: 弾力のある体 */
#define MUT3_XTRA_FAT                   0x00000020L /*!< 突然変異: 異常な肥満 */
#define MUT3_ALBINO                     0x00000040L /*!< 突然変異: アルビノ */
#define MUT3_FLESH_ROT                  0x00000080L /*!< 突然変異: 腐敗した肉体 */
#define MUT3_SILLY_VOI                  0x00000100L /*!< 突然変異: 間抜けなキーキー声 */
#define MUT3_BLANK_FAC                  0x00000200L /*!< 突然変異: のっぺらぼう */
#define MUT3_ILL_NORM                   0x00000400L /*!< 突然変異: 幻影に覆われた体 */
#define MUT3_XTRA_EYES                  0x00000800L /*!< 突然変異: 第三の目 */
#define MUT3_MAGIC_RES                  0x00001000L /*!< 突然変異: 魔法防御 */
#define MUT3_XTRA_NOIS                  0x00002000L /*!< 突然変異: 騒音 */
#define MUT3_INFRAVIS                   0x00004000L /*!< 突然変異: 赤外線視力 */
#define MUT3_XTRA_LEGS                  0x00008000L /*!< 突然変異: 追加の脚 */
#define MUT3_SHORT_LEG                  0x00010000L /*!< 突然変異: 短い脚 */
#define MUT3_ELEC_TOUC                  0x00020000L /*!< 突然変異: 電撃オーラ */
#define MUT3_FIRE_BODY                  0x00040000L /*!< 突然変異: 火炎オーラ */
#define MUT3_WART_SKIN                  0x00080000L /*!< 突然変異: イボ肌 */
#define MUT3_SCALES                     0x00100000L /*!< 突然変異: 鱗肌 */
#define MUT3_IRON_SKIN                  0x00200000L /*!< 突然変異: 鉄の肌 */
#define MUT3_WINGS                      0x00400000L /*!< 突然変異: 翼 */
#define MUT3_FEARLESS                   0x00800000L /*!< 突然変異: 恐れ知らず */
#define MUT3_REGEN                      0x01000000L /*!< 突然変異: 急回復 */
#define MUT3_ESP                        0x02000000L /*!< 突然変異: テレパシー */
#define MUT3_LIMBER                     0x04000000L /*!< 突然変異: しなやかな肉体 */
#define MUT3_ARTHRITIS                  0x08000000L /*!< 突然変異: 関節の痛み */
#define MUT3_BAD_LUCK                   0x10000000L /*!< 突然変異: 黒いオーラ(不運) */
#define MUT3_VULN_ELEM                  0x20000000L /*!< 突然変異: 元素攻撃弱点 */
#define MUT3_MOTION                     0x40000000L /*!< 突然変異: 正確で力強い動作 */
#define MUT3_GOOD_LUCK                  0x80000000L /*!< 突然変異: 白いオーラ(幸運) */

	s16b virtues[8];
	s16b vir_types[8];

	TIME_EFFECT word_recall;	  /* Word of recall counter */
	TIME_EFFECT alter_reality;	  /* Alter reality counter */
	DUNGEON_IDX recall_dungeon;      /* Dungeon set to be recalled */

	ENERGY energy_need;	  /* Energy needed for next move */
	ENERGY enchant_energy_need;	  /* Energy needed for next upkeep effect	 */

	FEED food;		  /* Current nutrition */

	/*
	 * p_ptr->special_attackによるプレイヤーの攻撃状態の定義 / Bit flags for the "p_ptr->special_attack" variable. -LM-
	 *
	 * Note:  The elemental and poison attacks should be managed using the
	 * function "set_ele_attack", in spell2.c.  This provides for timeouts and
	 * prevents the player from getting more than one at a time.
	 */
	BIT_FLAGS special_attack;
#define ATTACK_CONFUSE	0x00000001 /*!< プレイヤーのステータス:混乱打撃 */
#define ATTACK_XXX1		0x00000002 /*!< プレイヤーのステータス:未使用1 */
#define ATTACK_XXX2		0x00000004 /*!< プレイヤーのステータス:未使用2 */
#define ATTACK_XXX3	    0x00000008 /*!< プレイヤーのステータス:未使用3 */
#define ATTACK_ACID		0x00000010 /*!< プレイヤーのステータス:魔法剣/溶解 */
#define ATTACK_ELEC		0x00000020 /*!< プレイヤーのステータス:魔法剣/電撃 */
#define ATTACK_FIRE		0x00000040 /*!< プレイヤーのステータス:魔法剣/火炎 */
#define ATTACK_COLD		0x00000080 /*!< プレイヤーのステータス:魔法剣/冷凍 */
#define ATTACK_POIS		0x00000100 /*!< プレイヤーのステータス:魔法剣/毒殺 */
#define ATTACK_HOLY		0x00000200 /*!< プレイヤーのステータス:対邪?(未使用) */
#define ATTACK_SUIKEN	0x00000400 /*!< プレイヤーのステータス:酔拳 */

	/*
	 * p_ptr->special_defenseによるプレイヤーの防御状態の定義 / Bit flags for the "p_ptr->special_defense" variable. -LM-
	 */
	BIT_FLAGS special_defense;
#define DEFENSE_ACID	0x00000001 /*!< プレイヤーのステータス:酸免疫 */
#define DEFENSE_ELEC	0x00000002 /*!< プレイヤーのステータス:電撃免疫 */
#define DEFENSE_FIRE	0x00000004 /*!< プレイヤーのステータス:火炎免疫 */
#define DEFENSE_COLD	0x00000008 /*!< プレイヤーのステータス:冷気免疫 */
#define DEFENSE_POIS	0x00000010 /*!< プレイヤーのステータス:毒免疫 */
#define KAMAE_GENBU     0x00000020 /*!< プレイヤーのステータス:玄武の構え */
#define KAMAE_BYAKKO    0x00000040 /*!< プレイヤーのステータス:白虎の構え */
#define KAMAE_SEIRYU    0x00000080 /*!< プレイヤーのステータス:青竜の構え */
#define KAMAE_SUZAKU    0x00000100 /*!< プレイヤーのステータス:朱雀の構え */
#define KATA_IAI        0x00000200 /*!< プレイヤーのステータス:居合 */
#define KATA_FUUJIN     0x00000400 /*!< プレイヤーのステータス:風塵 */
#define KATA_KOUKIJIN   0x00000800 /*!< プレイヤーのステータス:降鬼陣 */
#define KATA_MUSOU      0x00001000 /*!< プレイヤーのステータス:無想 */
#define NINJA_KAWARIMI  0x00002000 /*!< プレイヤーのステータス:変わり身 */
#define NINJA_S_STEALTH 0x00004000 /*!< プレイヤーのステータス:超隠密 */
#define MAX_KAMAE 4 /*!< 修行僧の構え最大数 */
#define KAMAE_MASK (KAMAE_GENBU | KAMAE_BYAKKO | KAMAE_SEIRYU | KAMAE_SUZAKU) /*!< 修行僧の構えビット配列 */
#define MAX_KATA 4 /*!< 修行僧の型最大数 */
#define KATA_MASK (KATA_IAI | KATA_FUUJIN | KATA_KOUKIJIN | KATA_MUSOU) /*!< 修行僧の型ビット配列 */

	ACTION_IDX action;		  /* Currently action */
#define ACTION_NONE     0 /*!< 持続行動: なし */
#define ACTION_SEARCH   1 /*!< 持続行動: 探索 */
#define ACTION_REST     2 /*!< 持続行動: 休憩 */
#define ACTION_LEARN    3 /*!< 持続行動: 青魔法ラーニング */
#define ACTION_FISH     4 /*!< 持続行動: 釣り */
#define ACTION_KAMAE    5 /*!< 持続行動: 修行僧の構え */
#define ACTION_KATA     6 /*!< 持続行動: 剣術家の型 */
#define ACTION_SING     7 /*!< 持続行動: 歌 */
#define ACTION_HAYAGAKE 8 /*!< 持続行動: 早駆け */
#define ACTION_SPELL    9 /*!< 持続行動: 呪術 */

	BIT_FLAGS spell_learned1;	  /* bit mask of spells learned */
	BIT_FLAGS spell_learned2;	  /* bit mask of spells learned */
	BIT_FLAGS spell_worked1;	  /* bit mask of spells tried and worked */
	BIT_FLAGS spell_worked2;	  /* bit mask of spells tried and worked */
	BIT_FLAGS spell_forgotten1;	  /* bit mask of spells learned but forgotten */
	BIT_FLAGS spell_forgotten2;	  /* bit mask of spells learned but forgotten */
	SPELL_IDX spell_order[64];  /* order spells learned/remembered/forgotten */

	SUB_EXP spell_exp[64];        /* Proficiency of spells */
	SUB_EXP weapon_exp[5][64];    /* Proficiency of weapons */
	SUB_EXP skill_exp[GINOU_MAX]; /* Proficiency of misc. skill */

	MAGIC_NUM1 magic_num1[108];     /*!< Array for non-spellbook type magic */
	MAGIC_NUM2 magic_num2[108];     /*!< 魔道具術師の取り込み済魔道具使用回数 / Flags for non-spellbook type magics */

	SPELL_IDX mane_spell[MAX_MANE];
	HIT_POINT mane_dam[MAX_MANE];
	s16b mane_num;

	s16b concent;      /* Sniper's concentration level */

	HIT_POINT player_hp[PY_MAX_LEVEL];
	char died_from[80];   	  /* What killed the player */
	concptr last_message;        /* Last message on death or retirement */
	char history[4][60];  	  /* Textual "history" for the Player */

	u16b total_winner;	  /* Total winner */
	u16b panic_save;	  /* Panic save */

	u16b noscore;		  /* Cheating flags */

	bool wait_report_score;   /* Waiting to report score */
	bool is_dead;		  /* Player is dead */
	bool now_damaged;
	bool ambush_flag;

	bool wizard;		  /* Player is in wizard mode */

	MONSTER_IDX riding;              /* Riding on a monster of this index */
	byte knowledge;           /* Knowledge about yourself */
	BIT_FLAGS visit;               /* Visited towns */

	RACE_IDX start_race;          /* Race at birth */
	BIT_FLAGS old_race1;           /* Record of race changes */
	BIT_FLAGS old_race2;           /* Record of race changes */
	s16b old_realm;           /* Record of realm changes */

	s16b pet_follow_distance; /* Length of the imaginary "leash" for pets */
	s16b pet_extra_flags;     /* Various flags for controling pets */

	s16b today_mon;           /* Wanted monster */

	bool dtrap;               /* Whether you are on trap-safe grids */
	FLOOR_IDX floor_id;            /* Current floor location */

	bool autopick_autoregister; /* auto register is in-use or not */

	byte feeling;		/* Most recent dungeon feeling */
	s32b feeling_turn;	/* The turn of the last dungeon feeling */


	/*
	 * Indexes used for various "equipment" slots (hard-coded by savefiles, etc).
	 */
	#define INVEN_RARM      24 /*!< アイテムスロット…右手 */
	#define INVEN_LARM      25 /*!< アイテムスロット…左手 */
	#define INVEN_BOW       26 /*!< アイテムスロット…射撃 */
	#define INVEN_RIGHT     27 /*!< アイテムスロット…右手指 */
	#define INVEN_LEFT      28 /*!< アイテムスロット…左手指 */
	#define INVEN_NECK      29 /*!< アイテムスロット…首 */
	#define INVEN_LITE      30 /*!< アイテムスロット…光源 */
	#define INVEN_BODY      31 /*!< アイテムスロット…体 */
	#define INVEN_OUTER     32 /*!< アイテムスロット…体の上 */
	#define INVEN_HEAD      33 /*!< アイテムスロット…頭部 */
	#define INVEN_HANDS     34 /*!< アイテムスロット…腕部 */
	#define INVEN_FEET      35 /*!< アイテムスロット…脚部 */
	#define INVEN_AMMO      23 /*!< used for get_random_ego()  */
	#define INVEN_TOTAL     36 /*!< Total number of inventory_list slots (hard-coded). */
	#define INVEN_FORCE     1111 /*!< inventory_list slot for selecting force (hard-coded). */
	object_type *inventory_list; /* The player's inventory */
	s16b inven_cnt; /* Number of items in inventory */
	s16b equip_cnt; /* Number of items in equipment */

							/*** Temporary fields ***/

	bool playing;			/* True if player is playing */
	bool leaving;			/* True if player is leaving */

	bool monk_armour_aux;
	bool monk_notify_aux;

	byte leave_bldg;
	byte exit_bldg;			/* Goal obtained in arena? -KMW- */

	bool leaving_dungeon;	/* True if player is leaving the dungeon */
	bool teleport_town;
	bool enter_dungeon;     /* Just enter the dungeon */

	IDX health_who;	/* Health bar trackee */

	MONRACE_IDX monster_race_idx;	/* Monster race trackee */

	KIND_OBJECT_IDX object_kind_idx;	/* Object kind trackee */

	s16b new_spells;	/* Number of spells available */
	s16b old_spells;

	s16b old_food_aux;	/* Old value of food */

	bool old_cumber_armor;
	bool old_cumber_glove;
	bool old_heavy_wield[2];
	bool old_heavy_shoot;
	bool old_icky_wield[2];
	bool old_riding_wield[2];
	bool old_riding_ryoute;
	bool old_monlite;

	POSITION old_lite;		/* Old radius of lite (if any) */

	bool cumber_armor;	/* Mana draining armor */
	bool cumber_glove;	/* Mana draining gloves */
	bool heavy_wield[2];	/* Heavy weapon */
	bool heavy_shoot;	/* Heavy shooter */
	bool icky_wield[2];	/* Icky weapon */
	bool riding_wield[2];	/* Riding weapon */
	bool riding_ryoute;	/* Riding weapon */
	bool monlite;

	POSITION cur_lite;		/* Radius of lite (if any) */

	BIT_FLAGS update;	/* Pending Updates */
#define PU_BONUS        0x00000001L     /*!< ステータス更新フラグ: 能力値修正 / Calculate bonuses */
#define PU_TORCH        0x00000002L     /*!< ステータス更新フラグ: 光源半径 / Calculate torch radius */
#define PU_HP           0x00000010L     /*!< ステータス更新フラグ: HP / Calculate chp and mhp */
#define PU_MANA         0x00000020L     /*!< ステータス更新フラグ: MP / Calculate csp and msp */
#define PU_SPELLS       0x00000040L     /*!< ステータス更新フラグ: 魔法学習数 / Calculate spells */
#define PU_COMBINE      0x00000100L     /*!< アイテム処理フラグ: アイテムの結合を要する / Combine the pack */
#define PU_REORDER      0x00000200L     /*!< アイテム処理フラグ: アイテムの並び替えを要する / Reorder the pack */
#define PU_AUTODESTROY  0x00000400L     /*!< アイテム処理フラグ: アイテムの自動破壊を要する / Auto-destroy marked item */
#define PU_UN_VIEW      0x00010000L     /*!< ステータス更新フラグ: 地形の視界外化 / Forget view */
#define PU_UN_LITE      0x00020000L     /*!< ステータス更新フラグ: 明暗範囲の視界外化 / Forget lite */
#define PU_VIEW         0x00100000L     /*!< ステータス更新フラグ: 視界 / Update view */
#define PU_LITE         0x00200000L     /*!< ステータス更新フラグ: 明暗範囲 / Update lite */
#define PU_MON_LITE     0x00400000L     /*!< ステータス更新フラグ: モンスターの光源範囲 / Monster illumination */
#define PU_DELAY_VIS    0x00800000L     /*!< ステータス更新フラグ: 視界の追加更新 / Mega-Hack -- Delayed visual update */
#define PU_MONSTERS     0x01000000L     /*!< ステータス更新フラグ: モンスターのステータス / Update monsters */
#define PU_DISTANCE     0x02000000L     /*!< ステータス更新フラグ: プレイヤーとモンスターの距離 / Update distances */
#define PU_FLOW         0x10000000L     /*!< ステータス更新フラグ: プレイヤーから各マスへの到達距離 / Update flow */

	BIT_FLAGS redraw;	/* Normal Redraws */
	BIT_FLAGS window;	/* Window Redraws */

	s16b stat_use[A_MAX];	/* Current modified stats */
	s16b stat_top[A_MAX];	/* Maximal modified stats */

	bool sutemi;
	bool counter;

	ALIGNMENT align; /* Good/evil/neutral */
	POSITION run_py;
	POSITION run_px;
	DIRECTION fishing_dir;


	/*** Extracted fields ***/

	s16b running;			/* Current counter for running, if any */
	bool suppress_multi_reward; /*!< 複数レベルアップ時のパトロンからの報酬多重受け取りを防止 */

	WEIGHT total_weight;	/*!< 所持品と装備品の計算総重量 / Total weight being carried */

	s16b stat_add[A_MAX];	/* Modifiers to stat values */
	s16b stat_ind[A_MAX];	/* Indexes into stat tables */

	bool hack_mutation;
	bool is_fired;
	bool level_up_message;

	bool immune_acid;	/* Immunity to acid */
	bool immune_elec;	/* Immunity to lightning */
	bool immune_fire;	/* Immunity to fire */
	bool immune_cold;	/* Immunity to cold */

	bool resist_acid;	/* Resist acid */
	bool resist_elec;	/* Resist lightning */
	bool resist_fire;	/* Resist fire */
	bool resist_cold;	/* Resist cold */
	bool resist_pois;	/* Resist poison */

	bool resist_conf;	/* Resist confusion */
	bool resist_sound;	/* Resist sound */
	bool resist_lite;	/* Resist light */
	bool resist_dark;	/* Resist darkness */
	bool resist_chaos;	/* Resist chaos */
	bool resist_disen;	/* Resist disenchant */
	bool resist_shard;	/* Resist shards */
	bool resist_nexus;	/* Resist nexus */
	bool resist_blind;	/* Resist blindness */
	bool resist_neth;	/* Resist nether */
	bool resist_fear;	/* Resist fear */
	bool resist_time;	/* Resist time */
	bool resist_water;	/* Resist water */

	bool reflect;       /* Reflect 'bolt' attacks */
	bool sh_fire;       /* Fiery 'immolation' effect */
	bool sh_elec;       /* Electric 'immolation' effect */
	bool sh_cold;       /* Cold 'immolation' effect */

	bool anti_magic;    /* Anti-magic */
	bool anti_tele;     /* Prevent teleportation */

	bool sustain_str;	/* Keep strength */
	bool sustain_int;	/* Keep intelligence */
	bool sustain_wis;	/* Keep wisdom */
	bool sustain_dex;	/* Keep dexterity */
	bool sustain_con;	/* Keep constitution */
	bool sustain_chr;	/* Keep charisma */

	BIT_FLAGS cursed;	/* Player is cursed */

	bool can_swim;		/* No damage falling */
	bool levitation;		/* No damage falling */
	bool lite;		/* Permanent light */
	bool free_act;		/* Never paralyzed */
	bool see_inv;		/* Can see invisible */
	bool regenerate;	/* Regenerate hit pts */
	bool hold_exp;		/* Resist exp draining */

	bool telepathy;		/* Telepathy */
	bool esp_animal;
	bool esp_undead;
	bool esp_demon;
	bool esp_orc;
	bool esp_troll;
	bool esp_giant;
	bool esp_dragon;
	bool esp_human;
	bool esp_evil;
	bool esp_good;
	bool esp_nonliving;
	bool esp_unique;

	bool slow_digest;	/* Slower digestion */
	bool bless_blade;	/* Blessed blade */
	bool xtra_might;	/* Extra might bow */
	bool impact[2];		/* Earthquake blows */
	bool pass_wall;     /* Permanent wraithform */
	bool kill_wall;
	bool dec_mana;
	bool easy_spell;
	bool heavy_spell;
	bool warning;
	bool mighty_throw;
	bool see_nocto;		/* Noctovision */
	bool invoking_midnight_curse;

	DICE_NUMBER to_dd[2]; /* Extra dice/sides */
	DICE_SID to_ds[2];

	HIT_PROB dis_to_h[2];	/*!< 判明している現在の表記上の近接武器命中修正値 /  Known bonus to hit (wield) */
	HIT_PROB dis_to_h_b;	/*!< 判明している現在の表記上の射撃武器命中修正値 / Known bonus to hit (bow) */
	HIT_POINT dis_to_d[2];	/*!< 判明している現在の表記上の近接武器ダメージ修正値 / Known bonus to dam (wield) */
	ARMOUR_CLASS dis_to_a;	/*!< 判明している現在の表記上の装備AC修正値 / Known bonus to ac */
	ARMOUR_CLASS dis_ac;	/*!< 判明している現在の表記上の装備AC基礎値 / Known base ac */

	s16b to_h[2];		/* Bonus to hit (wield) */
	s16b to_h_b;		/* Bonus to hit (bow) */
	s16b to_h_m;		/* Bonus to hit (misc) */
	s16b to_d[2];		/* Bonus to dam (wield) */
	s16b to_d_m;		/* Bonus to dam (misc) */
	s16b to_a;			/* Bonus to ac */

	s16b to_m_chance;		/* Minusses to cast chance */

	bool ryoute;
	bool migite;
	bool hidarite;
	bool no_flowed;

	ARMOUR_CLASS ac;	/*!< 装備無しの基本AC / Base ac */

	ACTION_SKILL_POWER see_infra;	/*!< 赤外線視能力の強さ /Infravision range */
	ACTION_SKILL_POWER skill_dis;	/*!< 行動技能値:解除能力 / Skill: Disarming */
	ACTION_SKILL_POWER skill_dev;	/*!< 行動技能値:魔道具使用 / Skill: Magic Devices */
	ACTION_SKILL_POWER skill_sav;	/*!< 行動技能値:魔法防御 / Skill: Saving throw */
	ACTION_SKILL_POWER skill_stl;	/*!< 行動技能値:隠密 / Skill: Stealth factor */

	/*!
	 * 行動技能値:知覚 / Skill: Searching ability
	 * この値はsearch()による地形の隠し要素発見処理などで混乱、盲目、幻覚、無光源などの
	 * 状態異常がない限り、難易度修正などがないままそのままパーセンテージ値として使われる。
	 * 100以上ならば必ず全てのトラップなどを見つけることが出来る。
	 */
	ACTION_SKILL_POWER skill_srh;

	ACTION_SKILL_POWER skill_fos;	/*!< 行動技能値:探索 / Skill: Searching frequency */
	ACTION_SKILL_POWER skill_thn;	/*!< 行動技能値:打撃命中能力 / Skill: To hit (normal) */
	ACTION_SKILL_POWER skill_thb;	/*!< 行動技能値:射撃命中能力 / Skill: To hit (shooting) */
	ACTION_SKILL_POWER skill_tht;	/*!< 行動技能値:投射命中能力 / Skill: To hit (throwing) */
	ACTION_SKILL_POWER skill_dig;	/*!< 行動技能値:掘削 / Skill: Digging */

	s16b num_blow[2];	/* Number of blows */
	s16b num_fire;		/* Number of shots */

	byte tval_xtra;		/* Correct xtra tval */
	byte tval_ammo;		/* Correct ammo tval */

	byte pspeed;		/* Current speed */

	ENERGY energy_use;	/* Energy use this current_world_ptr->game_turn */

	POSITION y;	/* Player location in dungeon */
	POSITION x;	/* Player location in dungeon */
	GAME_TEXT name[32]; /*!< 現在のプレイヤー名 / Current player's character name */
	char base_name[32]; /*!< Stripped version of "player_name" */

};

extern concptr your_alignment(void);
extern int weapon_exp_level(int weapon_exp);
extern int riding_exp_level(int riding_exp);
extern int spell_exp_level(int spell_exp);

extern s16b calc_num_fire(object_type *o_ptr);
extern void calc_bonuses(void);
extern WEIGHT weight_limit(void);
extern bool has_melee_weapon(int i);
extern bool is_heavy_shoot(object_type *o_ptr);

extern bool heavy_armor(void);
extern void update_creature(player_type *creature_ptr);
extern BIT_FLAGS16 empty_hands(bool riding_control);
extern bool player_has_no_spellbooks(void);

extern void take_turn(player_type *creature_ptr, PERCENTAGE need_cost);
extern void free_turn(player_type *creature_ptr);

extern bool player_place(POSITION y, POSITION x);
extern void sanity_blast(monster_type *m_ptr, bool necro);

extern void check_experience(void);
extern void wreck_the_pattern(void);
extern void cnv_stat(int val, char *out_val);
extern s16b modify_stat_value(int value, int amount);
extern long calc_score(void);

extern const s32b player_exp[PY_MAX_LEVEL];
extern const s32b player_exp_a[PY_MAX_LEVEL];


/* Temporary flags macro */
#define IS_FAST() (p_ptr->fast || music_singing(MUSIC_SPEED) || music_singing(MUSIC_SHERO))
#define IS_INVULN() (p_ptr->invuln || music_singing(MUSIC_INVULN))
#define IS_HERO() (p_ptr->hero || music_singing(MUSIC_HERO) || music_singing(MUSIC_SHERO))
#define IS_BLESSED() (p_ptr->blessed || music_singing(MUSIC_BLESS) || hex_spelling(HEX_BLESS))
#define IS_OPPOSE_ACID() (p_ptr->oppose_acid || music_singing(MUSIC_RESIST) || (p_ptr->special_defense & KATA_MUSOU))
#define IS_OPPOSE_ELEC() (p_ptr->oppose_elec || music_singing(MUSIC_RESIST) || (p_ptr->special_defense & KATA_MUSOU))
#define IS_OPPOSE_FIRE() (p_ptr->oppose_fire || music_singing(MUSIC_RESIST) || (p_ptr->special_defense & KATA_MUSOU))
#define IS_OPPOSE_COLD() (p_ptr->oppose_cold || music_singing(MUSIC_RESIST) || (p_ptr->special_defense & KATA_MUSOU))
#define IS_OPPOSE_POIS() (p_ptr->oppose_pois || music_singing(MUSIC_RESIST) || (p_ptr->special_defense & KATA_MUSOU))
#define IS_TIM_ESP() (p_ptr->tim_esp || music_singing(MUSIC_MIND) || (p_ptr->concent >= CONCENT_TELE_THRESHOLD))
#define IS_TIM_STEALTH() (p_ptr->tim_stealth || music_singing(MUSIC_STEALTH))

#define P_PTR_KI (p_ptr->magic_num1[0])

/*
 * Player "food" crucial values
 */
#define PY_FOOD_MAX     15000   /*!< 食べ過ぎ～満腹の閾値 / Food value (Bloated) */
#define PY_FOOD_FULL    10000   /*!< 満腹～平常の閾値 / Food value (Normal) */
#define PY_FOOD_ALERT   2000    /*!< 平常～空腹の閾値 / Food value (Hungry) */
#define PY_FOOD_WEAK    1000    /*!< 空腹～衰弱の閾値 / Food value (Weak) */
#define PY_FOOD_FAINT   500     /*!< 衰弱～衰弱(赤表示/麻痺)の閾値 / Food value (Fainting) */
#define PY_FOOD_STARVE  100     /*!< 衰弱(赤表示/麻痺)～飢餓ダメージの閾値 / Food value (Starving) */

/*
 * Player regeneration constants
 */
#define PY_REGEN_NORMAL         197     /* Regen factor*2^16 when full */
#define PY_REGEN_WEAK           98      /* Regen factor*2^16 when weak */
#define PY_REGEN_FAINT          33      /* Regen factor*2^16 when fainting */
#define PY_REGEN_HPBASE         1442    /* Min amount hp regen*2^16 */
#define PY_REGEN_MNBASE         524     /* Min amount mana regen*2^16 */

#define CAN_TWO_HANDS_WIELDING() (!p_ptr->riding || (p_ptr->pet_extra_flags & PF_RYOUTE))


extern void cheat_death(player_type *creature_ptr);
