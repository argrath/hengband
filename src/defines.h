﻿#pragma once

/*!
 *  @file defines.h
 *  @brief 主要なマクロ定義ヘッダ / Purpose: global constants and macro definitions
 *  @date 2014/01/02
 *  @author
 * Copyright (c) 1997 Ben Harrison, James E. Wilson, Robert A. Koeneke\n
 *\n
 * This software may be copied and distributed for educational, research,\n
 * and not for profit purposes provided that this copyright and statement\n
 * are included in all such copies.  Other copyrights may also apply.\n
 *  @details
 * Do not edit this file unless you know *exactly* what you are doing.\n
 *\n
 * Some of the values in this file were chosen to preserve game balance,\n
 * while others are hard-coded based on the format of old save-files, the\n
 * definition of arrays in various places, mathematical properties, fast\n
 * computation, storage limits, or the format of external text files.\n
 *\n
 * Changing some of these values will induce crashes or memory errors or\n
 * savefile mis-reads.  Most of the comments in this file are meant as\n
 * reminders, not complete descriptions, and even a complete knowledge\n
 * of the source may not be sufficient to fully understand the effects\n
 * of changing certain definitions.\n
 *\n
 * Lastly, note that the code does not always use the symbolic constants\n
 * below, and sometimes uses various hard-coded values that may not even\n
 * be defined in this file, but which may be related to definitions here.\n
 * This is of course bad programming practice, but nobody is perfect...\n
 *\n
 * For example, there are MANY things that depend on the screen being\n
 * 80x24, with the top line used for messages, the bottom line being\n
 * used for status, and exactly 22 lines used to show the dungeon.\n
 * Just because your screen can hold 46 lines does not mean that the\n
 * game will work if you try to use 44 lines to show the dungeon.\n
 *\n
 * You have been warned.\n
 */


/*!
 * @brief 表示上の基本的なパネル単位(垂直方向、BLOCK_HGTの倍数で設定すること)
 * Number of grids in each panel (vertically) Must be a multiple of BLOCK_HGT
 */
#define PANEL_HGT 11

/*!
 * @brief 表示上の基本的なパネル単位(水平方向、BLOCK_WIDの倍数で設定すること)
 * Number of grids in each panel (horizontally) Must be a multiple of BLOCK_WID
 */
#define PANEL_WID 33

/*!
 * @brief 表示上の基本的なブロック単位(垂直方向、PANEL_HGTの倍数で設定すること)
 * Number of grids used to display the dungeon (vertically). Must be a multiple of 11, probably hard-coded to 22.
 */
#define SCREEN_HGT 22

/*!
 * @brief 表示上の基本的なブロック単位(水平方向、PANEL_WIDの倍数で設定すること)
 * Number of grids used to display the dungeon (horizontally). Must be a multiple of 33, probably hard-coded to 66.
 */
#define SCREEN_WID 66

/*!
 * @brief 表示上のダンジョンの最大垂直サイズ(SCREEN_HGTの3倍が望ましい)
 * Maximum dungeon height in grids, must be a multiple of SCREEN_HGT, probably hard-coded to SCREEN_HGT * 3.
 */
#define MAX_HGT 66

/*!
 * @brief 表示上のダンジョンの最大水平サイズ(SCREEN_WIDの3倍が望ましい)
 * Maximum dungeon width in grids, must be a multiple of SCREEN_WID, probably hard-coded to SCREEN_WID * 3.
 */
#define MAX_WID 198

/*
 * Arena constants
 */
#define ARENA_DEFEATED_OLD_VER (-(MAX_SHORT)) /*<! 旧バージョンの闘技場敗北定義 */

#define MAX_SEXES        2 /*!< 性別の定義最大数 / Maximum number of player "sex" types (see "table.c", etc) */
#define MAX_CLASS       28 /*!< 職業の最大定義数 Maximum number of player "class" types (see "table.c", etc) */
#define MAX_SEIKAKU     13 /*!< 性格の最大定義数 */

#define MAX_MIND_POWERS  21 /*!< 超能力の数 / Mindcraft */

/*
 * Size of memory reserved for initialization of some arrays
 */
#define FAKE_NAME_SIZE  40 * 1024L /*!< ゲーム情報の種別毎に用意される名前用バッファの容量 */
#define FAKE_TEXT_SIZE 150 * 1024L /*!< ゲーム情報の種別毎に用意されるテキスト用バッファの容量 */
#define FAKE_TAG_SIZE   10 * 1024L /*!< ゲーム情報の種別毎に用意されるタグ用バッファの容量 */

#define MAX_HISCORES    999 /*!< スコア情報保存の最大数 / Maximum number of high scores in the high score file */

/*!
 * @brief プレイヤー用光源処理配列サイズ / Maximum size of the "lite" array (see "current_floor_ptr->grid_array.c")
 * @details Note that the "lite radius" will NEVER exceed 14, and we would
 * never require more than 581 entries in the array for circular "lite".
 */
#define LITE_MAX 600

/*!
 * @brief モンスター用光源処理配列サイズ / Maximum size of the "mon_lite" array (see "current_floor_ptr->grid_array.c")
 * @details Note that the "view radius" will NEVER exceed 20, monster illumination
 * flags are dependent on CAVE_VIEW, and even if the "view" was octagonal,
 * we would never require more than 1520 entries in the array.
 */
#define MON_LITE_MAX 1536

/*!
 * @brief 視界処理配列サイズ / Maximum size of the "view" array (see "current_floor_ptr->grid_array.c")
 * @details Note that the "view radius" will NEVER exceed 20, and even if the "view"
 * was octagonal, we would never require more than 1520 entries in the array.
 */
#define VIEW_MAX 1536

/*!
 * @brief 視界及び光源の過渡処理配列サイズ / Maximum size of the "temp" array (see "current_floor_ptr->grid_array.c")
 * @details We must be as large as "VIEW_MAX" and "LITE_MAX" for proper functioning
 * of "update_view()" and "update_lite()".  We must also be as large as the
 * largest illuminatable room, but no room is larger than 800 grids.  We
 * must also be large enough to allow "good enough" use as a circular queue,
 * to calculate monster flow, but note that the flow code is "paranoid".
 */
#define TEMP_MAX 2298

/*!
 * @brief 再描画処理用配列サイズ / Maximum size of the "redraw" array (see "current_floor_ptr->grid_array.c")
 * @details We must be large for proper functioning of delayed redrawing.
 * We must also be as large as two times of the largest view area.
 * Note that maximum view grids are 1149 entries.
 */
#define REDRAW_MAX 2298


/*!
 * @brief マクロ登録の最大数 / Maximum number of macros (see "io.c")
 * @note Default: assume at most 256 macros are used
 */
#define MACRO_MAX       256

/*!
 * @brief 銘情報の最大数 / Maximum number of "quarks" (see "io.c")
 * @note 
 * Default: assume at most 512 different inscriptions are used<br>
 * Was 512... 256 quarks added for random artifacts<br>
 */
#define QUARK_MAX       768

/*
 * OPTION: Maximum number of messages to remember (see "io.c")
 * Default: assume maximal memorization of 2048 total messages
 */
#define MESSAGE_MAX  81920

/*
 * OPTION: Maximum space for the message text buffer (see "io.c")
 * Default: assume that each of the 2048 messages is repeated an
 * average of three times, and has an average length of 48
 */
#define MESSAGE_BUF 655360


/*
 * Maximum number of "normal" pack slots, and the index of the "overflow"
 * slot, which can hold an item, but only temporarily, since it causes the
 * pack to "overflow", dropping the "last" item onto the ground.  Since this
 * value is used as an actual slot, it must be less than "INVEN_RARM" (below).
 * Note that "INVEN_PACK" is probably hard-coded by its use in savefiles, and
 * by the fact that the screen can only show 23 items plus a one-line prompt.
 */
#define INVEN_PACK      23 /*!< アイテムスロット…所持品(0～) */

/*
 * Player sex constants (hard-coded by save-files, arrays, etc)
 */
#define SEX_FEMALE              0
#define SEX_MALE                1

/*** Screen Locations ***/

#define VER_INFO_ROW 3   //!< タイトル表記(行)


#define ROW_MAP                 0
#define COL_MAP                 12


/* Which features are dynamic */
#define have_dynamic_flags(ARRAY) \
	(!!((ARRAY)[(FF_INSTANT / 32)] & \
	    ((1UL << (FF_INSTANT % 32)) | \
	     (1UL << (FF_EXPLODE % 32)) | \
	     (1UL << (FF_TIMED % 32)) | \
	     (1UL << (FF_ERUPT % 32)) | \
	     (1UL << (FF_STRIKE % 32)) | \
	     (1UL << (FF_SPREAD % 32)))))

#define feat_locked_door_random(DOOR_TYPE) \
	(feat_door[(DOOR_TYPE)].num_locked ? \
	 feat_door[(DOOR_TYPE)].locked[randint0(feat_door[(DOOR_TYPE)].num_locked)] : feat_none)

#define feat_jammed_door_random(DOOR_TYPE) \
	(feat_door[(DOOR_TYPE)].num_jammed ? \
	 feat_door[(DOOR_TYPE)].jammed[randint0(feat_door[(DOOR_TYPE)].num_jammed)] : feat_none)


/*
 * Bit flags for the *_can_enter() and monster_can_cross_terrain()
 */
#define CEM_RIDING              0x0001
#define CEM_P_CAN_ENTER_PATTERN 0x0002


#define OBJ_GOLD_LIST   480     /* First "gold" entry */
#define MAX_GOLD        18      /* Number of "gold" entries */

/*
 * Object flags
 *
 * Old variables for object flags such as flags1, flags2, and flags3
 * are obsolated.  Now single array flgs[TR_FLAG_SIZE] contains all
 * object flags.  And each flag is refered by single index number
 * instead of a bit mask.
 *
 * Therefore it's very easy to add a lot of new flags; no one need to
 * worry about in which variable a new flag should be put, nor to
 * modify a huge number of files all over the source directory at once
 * to add new flag variables such as flags4, a_ability_flags1, etc...
 *
 * All management of flags is now treated using a set of macros
 * instead of bit operations.
 * Note: These macros are using division, modulo, and bit shift
 * operations, and it seems that these operations are rather slower
 * than original bit operation.  But since index numbers are almost
 * always given as constant, such slow operations are performed in the
 * compile time.  So there is no problem on the speed.
 *
 * Exceptions of new flag management is a set of flags to control
 * object generation and the curse flags.  These are not yet rewritten
 * in new index form; maybe these have no merit of rewriting.
 */

#define have_flag(ARRAY, INDEX) !!((ARRAY)[(INDEX)/32] & (1L << ((INDEX)%32)))
#define add_flag(ARRAY, INDEX) ((ARRAY)[(INDEX)/32] |= (1L << ((INDEX)%32)))
#define remove_flag(ARRAY, INDEX) ((ARRAY)[(INDEX)/32] &= ~(1L << ((INDEX)%32)))
#define is_pval_flag(INDEX) ((TR_STR <= (INDEX) && (INDEX) <= TR_MAGIC_MASTERY) || (TR_STEALTH <= (INDEX) && (INDEX) <= TR_BLOWS))
#define have_pval_flags(ARRAY) !!((ARRAY)[0] & (0x00003f7f))

/*
 * Is the monster seen by the player?
 */
#define is_seen(A) \
	((bool)((A)->ml && (!ignore_unview || p_ptr->inside_battle || \
	 (player_can_see_bold((A)->fy, (A)->fx) && projectable(p_ptr->y, p_ptr->x, (A)->fy, (A)->fx)))))


/*** Color constants ***/


/*
 * Hack -- attempt to reduce various values
 */
#ifdef ANGBAND_LITE
# undef MACRO_MAX
# define MACRO_MAX      128
# undef QUARK_MAX
# define QUARK_MAX      128
# undef MESSAGE_MAX
# define MESSAGE_MAX    128
# undef MESSAGE_BUF
# define MESSAGE_BUF    4096
#endif

#ifdef JP
#define JVERB_AND 1
#define JVERB_TO  2
#define JVERB_OR  3
#endif

/*
 * Modes for the tokenizer
 */
#define TOKENIZE_CHECKQUOTE 0x01  /* Special handling of single quotes */

#define GINOU_MAX      10


#define MAX_MANE 16


#define EATER_EXT 36
#define EATER_CHARGE 0x10000L
#define EATER_ROD_CHARGE 0x10L


#define DETECT_RAD_DEFAULT 30
#define DETECT_RAD_MAP     30
#define DETECT_RAD_ALL     255

/* Maximum "Nazguls" number */
#define MAX_NAZGUL_NUM 5

#define VIRTUE_LARGE 1
#define VIRTUE_SMALL 2

#define SPELL_DD_S 27
#define SPELL_DD_T 13
#define SPELL_SW   22
#define SPELL_KABE 20

#define KNOW_STAT   0x01
#define KNOW_HPRATE 0x02



#define DUNGEON_FEAT_PROB_NUM 3

/*
 * Flags for save/load temporal saved floor file
 */
#define SLF_SECOND     	 0x0001  /* Called from another save/load function */
#define SLF_NO_KILL      0x0002  /* Don't kill temporal files */


/* Sub-alignment flags for neutral monsters */
#define SUB_ALIGN_NEUTRAL 0x0000
#define SUB_ALIGN_EVIL    0x0001
#define SUB_ALIGN_GOOD    0x0002

/* Is "teleport level" ineffective to this target? */
#define TELE_LEVEL_IS_INEFF(TARGET) \
	(p_ptr->inside_arena || p_ptr->inside_battle || \
	 (p_ptr->inside_quest && !random_quest_number(current_floor_ptr->dun_level)) || \
	 (((TARGET) <= 0) && (quest_number(current_floor_ptr->dun_level) || (current_floor_ptr->dun_level >= d_info[p_ptr->dungeon_idx].maxdepth)) && \
	  (current_floor_ptr->dun_level >= 1) && ironman_downward))


/*
 * Max numbers of macro trigger names
 */
#define MAX_MACRO_MOD 12
#define MAX_MACRO_TRIG 200 /*!< 登録を許すマクロ（トリガー）の最大数 */

/* Max size of screen dump buffer */
#define SCREEN_BUF_MAX_SIZE (4 * 65536)

#define MTIMED_CSLEEP   0 /* Monster is sleeping */
#define MTIMED_FAST     1 /* Monster is temporarily fast */
#define MTIMED_SLOW     2 /* Monster is temporarily slow */
#define MTIMED_STUNNED  3 /* Monster is stunned */
#define MTIMED_CONFUSED 4 /* Monster is confused */
#define MTIMED_MONFEAR  5 /* Monster is afraid */
#define MTIMED_INVULNER 6 /* Monster is temporarily invulnerable */

#define MAX_MTIMED      7

#define MON_CSLEEP(M_PTR)   ((M_PTR)->mtimed[MTIMED_CSLEEP])
#define MON_FAST(M_PTR)     ((M_PTR)->mtimed[MTIMED_FAST])
#define MON_SLOW(M_PTR)     ((M_PTR)->mtimed[MTIMED_SLOW])
#define MON_STUNNED(M_PTR)  ((M_PTR)->mtimed[MTIMED_STUNNED])
#define MON_CONFUSED(M_PTR) ((M_PTR)->mtimed[MTIMED_CONFUSED])
#define MON_MONFEAR(M_PTR)  ((M_PTR)->mtimed[MTIMED_MONFEAR])
#define MON_INVULNER(M_PTR) ((M_PTR)->mtimed[MTIMED_INVULNER])

/*
 * Bit flags for screen_object()
 */
#define SCROBJ_FAKE_OBJECT  0x00000001
#define SCROBJ_FORCE_DETAIL 0x00000002

/*
 * For travel command (auto run)
 */
#define TRAVEL

#define CONCENT_RADAR_THRESHOLD 2
#define CONCENT_TELE_THRESHOLD  5

/* Hex */
#define hex_spelling_any() \
	((p_ptr->realm1 == REALM_HEX) && (p_ptr->magic_num1[0]))
#define hex_spelling(X) \
	((p_ptr->realm1 == REALM_HEX) && (p_ptr->magic_num1[0] & (1L << (X))))
#define CASTING_HEX_FLAGS(P_PTR) ((P_PTR)->magic_num1[0])
#define CASTING_HEX_NUM(P_PTR) ((P_PTR)->magic_num2[0])
#define HEX_REVENGE_POWER(P_PTR) ((P_PTR)->magic_num1[2])
#define HEX_REVENGE_TURN(P_PTR) ((P_PTR)->magic_num2[2])
#define HEX_REVENGE_TYPE(P_PTR) ((P_PTR)->magic_num2[1])

/*
  Language selection macro
*/
#ifdef JP
#define _(JAPANESE,ENGLISH) (JAPANESE)
#else
#define _(JAPANESE,ENGLISH) (ENGLISH)
#endif

/* Lite flag macro */
#define have_lite_flag(ARRAY) \
	(have_flag(ARRAY, TR_LITE_1) || have_flag(ARRAY, TR_LITE_2) || have_flag(ARRAY, TR_LITE_3))

#define have_dark_flag(ARRAY) \
	(have_flag(ARRAY, TR_LITE_M1) || have_flag(ARRAY, TR_LITE_M2) || have_flag(ARRAY, TR_LITE_M3))

/* Spell Type flag */
#define MONSTER_TO_PLAYER     0x01
#define MONSTER_TO_MONSTER    0x02

/* summoning number */
#define S_NUM_6     (easy_band ? 2 : 6)
#define S_NUM_4     (easy_band ? 1 : 4)

/* monster spell number */
#define RF4_SPELL_START 32 * 3
#define RF5_SPELL_START 32 * 4
#define RF6_SPELL_START 32 * 5

#define RF4_SPELL_SIZE 32
#define RF5_SPELL_SIZE 32
#define RF6_SPELL_SIZE 32

/* Spell Damage Calc Flag*/
#define DAM_ROLL 1
#define DAM_MAX 2
#define DAM_MIN 3
#define DICE_NUM 4
#define DICE_SIDE 5
#define DICE_MULT 6
#define DICE_DIV 7
#define BASE_DAM 8

/* Cheat Info Type */
#define CHEAT_OBJECT 0
#define CHEAT_MONSTER 1
#define CHEAT_DUNGEON 2
#define CHEAT_MISC 3

#define COMMAND_ARG_REST_UNTIL_DONE -2   /*!<休憩コマンド引数 … 必要な分だけ回復 */
#define COMMAND_ARG_REST_FULL_HEALING -1 /*!<休憩コマンド引数 … HPとMPが全回復するまで */

/*!
 * チートオプションの最大数 / Number of cheating options
 */
#define CHEAT_MAX 10
