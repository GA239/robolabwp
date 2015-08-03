//
//  MZMoveResultCode.h
//
//  “ип, определ€ющий возможные результаты хода пользовател€.

#ifndef _MZMoveResultCode_h
#define _MZMoveResultCode_h

typedef enum
{
    MOTION_IMPOSSIBLE = 1,
    MOTION_PERFORMED = 2,
    GAME_ENDED = 4,
    GAME_PAUSED = 8,
	NEEDS_UPDATE = 16
} MZMoveResultCode;

#endif
