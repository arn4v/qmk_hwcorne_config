#define VIAL_KEYBOARD_UID {0xEE, 0x84, 0x60, 0x93, 0x35, 0x96, 0x52, 0x07}
#define VIAL_UNLOCK_COMBO_ROWS {0,0}
#define VIAL_UNLOCK_COMBO_COLS {0,1}

// Increase layer count for Vial
#define DYNAMIC_KEYMAP_LAYER_COUNT 6

// Tapping term configuration
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS

// Combo configuration
#define COMBO_COUNT 0
#define COMBO_TERM 50

// Mouse key configuration
#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL

// Additional features
#define FORCE_NKRO

// Force left half as the master
#define MASTER_LEFT

// Debounce settings for handwired builds
#define DEBOUNCE 10
#define DEBOUNCE_TYPE sym_defer_pk

// Matrix scan settle time (microseconds) for handwired matrices
#define MATRIX_IO_DELAY 50
