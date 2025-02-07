/*

libScePad

Copyright by Sony Computer Entertainment
Header by github/MasonLeeBack

*/


#ifndef _LIBSCEPAD_H_
#define _LIBSCEPAD_H_

#include <stdint.h>

#if !defined(_WIN32) || !defined(_WIN64)
#error This library is only compatible with Windows 64-bit systems.
#endif

#ifndef _SCE_PAD_TRIGGER_EFFECT_H
#define _SCE_PAD_TRIGGER_EFFECT_H

#define SCE_PAD_TRIGGER_EFFECT_TRIGGER_MASK_L2			0x01
#define SCE_PAD_TRIGGER_EFFECT_TRIGGER_MASK_R2			0x02

#define SCE_PAD_TRIGGER_EFFECT_PARAM_INDEX_FOR_L2		0
#define SCE_PAD_TRIGGER_EFFECT_PARAM_INDEX_FOR_R2		1

#define SCE_PAD_TRIGGER_EFFECT_TRIGGER_NUM				2

/* Definition of control point num */
#define SCE_PAD_TRIGGER_EFFECT_CONTROL_POINT_NUM		10

typedef enum ScePadTriggerEffectMode{
	SCE_PAD_TRIGGER_EFFECT_MODE_OFF,
	SCE_PAD_TRIGGER_EFFECT_MODE_FEEDBACK,
	SCE_PAD_TRIGGER_EFFECT_MODE_WEAPON,
	SCE_PAD_TRIGGER_EFFECT_MODE_VIBRATION,
	SCE_PAD_TRIGGER_EFFECT_MODE_MULTIPLE_POSITION_FEEDBACK,
	SCE_PAD_TRIGGER_EFFECT_MODE_SLOPE_FEEDBACK,
	SCE_PAD_TRIGGER_EFFECT_MODE_MULTIPLE_POSITION_VIBRATION,
} ScePadTriggerEffectMode;

/**
 *E  
 *  @brief parameter for setting the trigger effect to off mode.
 *         Off Mode: Stop trigger effect.
 **/
typedef struct ScePadTriggerEffectOffParam{
	uint8_t padding[48];
} ScePadTriggerEffectOffParam;

/**
 *E  
 *  @brief parameter for setting the trigger effect to Feedback mode.
 *         Feedback Mode: The motor arm pushes back trigger.
 *                        Trigger obtains stiffness at specified position.
 **/
typedef struct ScePadTriggerEffectFeedbackParam{
	uint8_t position;	/*E position where the strength of target trigger start changing(0~9). */
	uint8_t strength;	/*E strength that the motor arm pushes back target trigger(0~8 (0: Same as Off mode)). */
	uint8_t padding[46];
} ScePadTriggerEffectFeedbackParam;

/**
 *E  
 *  @brief parameter for setting the trigger effect to Weapon mode.
 *         Weapon Mode: Emulate weapon like gun trigger.
 **/
typedef struct ScePadTriggerEffectWeaponParam{
	uint8_t startPosition;	/*E position where the stiffness of trigger start changing(2~7). */
	uint8_t endPosition;	/*E position where the stiffness of trigger finish changing(startPosition+1~8). */
	uint8_t strength;		/*E strength of gun trigger(0~8 (0: Same as Off mode)). */
	uint8_t padding[45];
} ScePadTriggerEffectWeaponParam;

/**
 *E  
 *  @brief parameter for setting the trigger effect to Vibration mode.
 *         Vibration Mode: Vibrates motor arm around specified position.
 **/
typedef struct ScePadTriggerEffectVibrationParam{
	uint8_t position;	/*E position where the motor arm start vibrating(0~9). */
	uint8_t amplitude;	/*E vibration amplitude(0~8 (0: Same as Off mode)). */
	uint8_t frequency;	/*E vibration frequency(0~255[Hz] (0: Same as Off mode)). */
	uint8_t padding[45];
} ScePadTriggerEffectVibrationParam;

/**
 *E  
 *  @brief parameter for setting the trigger effect to ScePadTriggerEffectMultiplePositionFeedbackParam mode.
 *         Multi Position Feedback Mode: The motor arm pushes back trigger.
 *                                       Trigger obtains specified stiffness at each control point.
 **/
typedef struct ScePadTriggerEffectMultiplePositionFeedbackParam{
	uint8_t strength[SCE_PAD_TRIGGER_EFFECT_CONTROL_POINT_NUM];	/*E strength that the motor arm pushes back target trigger at position(0~8 (0: Same as Off mode)).
																 *  strength[0] means strength of motor arm at position0.
																 *  strength[1] means strength of motor arm at position1.
																 *  ...
																 * */
	uint8_t padding[38];
} ScePadTriggerEffectMultiplePositionFeedbackParam;

/**
 *E  
 *  @brief parameter for setting the trigger effect to Feedback3 mode.
 *         Slope Feedback Mode: The motor arm pushes back trigger between two spedified control points.
 *                              Stiffness of the trigger is changing depending on the set place.
 **/
typedef struct ScePadTriggerEffectSlopeFeedbackParam{

	uint8_t startPosition;	/*E position where the strength of target trigger start changing(0~endPosition). */
	uint8_t endPosition; 	/*E position where the strength of target trigger finish changing(startPosition+1~9). */
	uint8_t startStrength;	/*E strength when trigger's position is startPosition(1~8) */
	uint8_t endStrength;	/*E strength when trigger's position is endPosition(1~8) */
	uint8_t padding[44];
} ScePadTriggerEffectSlopeFeedbackParam;

/**
 *E  
 *  @brief parameter for setting the trigger effect to Vibration2 mode.
 *         Multi Position Vibration Mode: Vibrates motor arm around specified control point.
 *                                        Trigger vibrates specified amplitude at each control point.
 **/
typedef struct ScePadTriggerEffectMultiplePositionVibrationParam{
	uint8_t frequency;												/*E vibration frequency(0~255 (0: Same as Off mode)) */
	uint8_t amplitude[SCE_PAD_TRIGGER_EFFECT_CONTROL_POINT_NUM];	/*E vibration amplitude at position(0~8 (0: Same as Off mode)).
																	 *  amplitude[0] means amplitude of vibration at position0.
																	 *  amplitude[1] means amplitude of vibration at position1.
																	 *  ...
																	 * */
	uint8_t padding[37];
} ScePadTriggerEffectMultiplePositionVibrationParam;

/**
 *E  
 *  @brief parameter for setting the trigger effect mode.
 **/
typedef union ScePadTriggerEffectCommandData{
	ScePadTriggerEffectOffParam							offParam;
	ScePadTriggerEffectFeedbackParam					feedbackParam;
	ScePadTriggerEffectWeaponParam						weaponParam;
	ScePadTriggerEffectVibrationParam					vibrationParam;
	ScePadTriggerEffectMultiplePositionFeedbackParam	multiplePositionFeedbackParam;
	ScePadTriggerEffectSlopeFeedbackParam				slopeFeedbackParam;
	ScePadTriggerEffectMultiplePositionVibrationParam	multiplePositionVibrationParam;
} ScePadTriggerEffectCommandData;

/**
 *E  
 *  @brief parameter for setting the trigger effect.
 **/
typedef struct ScePadTriggerEffectCommand{
	ScePadTriggerEffectMode mode;
	uint8_t padding[4];
	ScePadTriggerEffectCommandData commandData;
} ScePadTriggerEffectCommand;

/**
 *E  
 *  @brief parameter for the scePadSetTriggerEffect function.
 **/
typedef struct ScePadTriggerEffectParam{

	uint8_t triggerMask;		/*E Set trigger mask to activate trigger effect commands.
								 *  SCE_PAD_TRIGGER_EFFECT_TRIGGER_MASK_L2 : 0x01
								 *  SCE_PAD_TRIGGER_EFFECT_TRIGGER_MASK_R2 : 0x02
								 * */
	uint8_t padding[7];

	ScePadTriggerEffectCommand command[SCE_PAD_TRIGGER_EFFECT_TRIGGER_NUM];	/*E command[SCE_PAD_TRIGGER_EFFECT_PARAM_INDEX_FOR_L2] is for L2 trigger setting
																			 *  and param[SCE_PAD_TRIGGER_EFFECT_PARAM_INDEX_FOR_R2] is for R2 trgger setting.
																			 * */
} ScePadTriggerEffectParam;

#if defined(__cplusplus) && __cplusplus >= 201103L
static_assert( sizeof( ScePadTriggerEffectParam ) == 120, "ScePadTriggerEffectParam has incorrect size" );
#endif

#endif /* _SCE_PAD_TRIGGER_EFFECT_H */

// Error codes
#define SCE_OK 0

// Haptic feedback / Standard Rumble flags
#define DS_HAPTICS_MODE 0x01
#define DS_RUMBLE_MODE 0x02

// Audio path
#define DS_AUDIO_PATH_STEREO_HEADSET 0x00
#define DS_AUDIO_PATH_MONO_LEFT_HEADSET 0x01
#define DS_AUDIO_PATH_MONO_LEFT_HEADSET_AND_SPEAKER 0x02
#define DS_AUDIO_PATH_ONLY_SPEAKER 0x03

// Bus type
#define SCE_BUS_TYPE_UNKNOWN 0
#define SCE_BUS_TYPE_USB 1
#define SCE_BUS_TYPE_BT 2

// Button mask
#define SCE_BM_CROSS    0x00004000
#define SCE_BM_CIRCLE   0x00002000
#define SCE_BM_TRIANGLE 0x00001000
#define SCE_BM_SQUARE   0x00008000

#define SCE_BM_L1       0x00000400
#define SCE_BM_L2       0x00000100
#define SCE_BM_R1       0x00000800
#define SCE_BM_R2       0x00000200

#define SCE_BM_L3       0x00000002
#define SCE_BM_R3       0x00000004

#define SCE_BM_N_DPAD   0x00000010
#define SCE_BM_S_DPAD   0x00000040
#define SCE_BM_E_DPAD   0x00000020
#define SCE_BM_W_DPAD   0x00000080

#define SCE_BM_OPTIONS  0x00000008

#define SCE_BM_TOUCH    0x00100000

// Call sceSetParticularMode(true) to use these
#define SCE_BM_SHARE    0x00000001
#define SCE_BM_PSBTN    0x00010000

typedef struct {
	uint8_t X;
	uint8_t Y;
} s_SceStickData;

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} s_SceLightBar;

struct s_SceFQuaternion {
	float x, y, z, w;
};

struct s_SceFVector3 {
	float x, y, z;
};

struct s_ScePadTouch {
	uint16_t x;
	uint16_t y;
	uint8_t id;
	uint8_t reserve[3];
};

struct s_ScePadTouchData {
	uint8_t touchNum;
	uint8_t reserve[3];
	uint32_t reserve1;
	s_ScePadTouch touch[2];
};

struct s_ScePadExtensionUnitData {
	uint32_t extensionUnitId;
	uint8_t reserve[1];
	uint8_t dataLength;
	uint8_t data[10];
};

struct s_ScePadVibrationParam {
    uint8_t largeMotor;
    uint8_t smallMotor;
};

struct s_ScePadVolumeGain {
	uint8_t speakerVolume;
	uint8_t headsetVolume;
	uint8_t padding;
	uint8_t micGain;
};

#pragma pack(push, 1) 
struct s_ScePadContainerIdInfo {
    DWORD size;              
    wchar_t id[0x2000];  
};
#pragma pack(pop)

struct s_ScePadInfo {
    float batteryLevel; 
    WORD touchpadWidth;       
    WORD touchpadHeight; 
    BYTE flag1;         
    BYTE flag2;          
    BYTE state;         
    BYTE isValid; 
};

// TODO: Things to be figured out later
//      Offsets for the gyroscope, touchpad, etc.
// 120 bytes
typedef struct {
	uint32_t bitmask_buttons;
	s_SceStickData LeftStick;
	s_SceStickData RightStick;
	uint8_t L2_Analog;
	uint8_t R2_Analog;
	uint16_t padding;
	s_SceFQuaternion orientation;
	s_SceFVector3 acceleration;
	s_SceFVector3 angularVelocity;
	s_ScePadTouchData touchData;
	bool connected;
	uint64_t timeStamp;

} s_ScePadData;

enum s_SceControllerType {
	UNKNOWN = 0,
	DUALSHOCK_4 = 1,
	DUALSENSE = 2
};

#ifdef __cplusplus
extern "C" {
#endif

int scePadClose(int handle);
int scePadGetContainerIdInformation(int handle, s_ScePadContainerIdInfo* containerIdInfo);
int scePadGetControllerBusType(int handle, int* busType);
int scePadGetControllerInformation(int handle, s_ScePadInfo* info);
int scePadGetControllerType(int handle, s_SceControllerType* controllerType);
int scePadGetHandle(int userID, int, int);
int scePadGetJackState(int handle, int state[4]);
bool scePadGetParticularMode(void);
int scePadGetTriggerEffectState(int handle, int state[2]);
int scePadInit(void);
int scePadIsControllerUpdateRequired(int handle);
int scePadIsSupportedAudioFunction(int handle);
int scePadOpen(int userID, int, int, void*);
int scePadRead(int handle, void* data, int count);
int scePadReadState(int handle, s_ScePadData* data);
int scePadResetLightBar(int handle);
int scePadResetOrientation(int handle);
int scePadSetAngularVelocityDeadbandState(int handle, bool state);
int scePadSetAudioOutPath(int handle, int path);
int scePadSetLightBar(int handle, s_SceLightBar* lightbar);
int scePadSetMotionSensorState(int handle, bool state);
int scePadSetParticularMode(bool mode);
int scePadSetTiltCorrectionState(int handle, bool state);
int scePadSetTriggerEffect(int handle, ScePadTriggerEffectParam* triggerEffect);
int scePadSetVibration(int handle, s_ScePadVibrationParam* vibration);
int scePadSetVibrationMode(int handle, int mode);
int scePadSetVolumeGain(int handle, s_ScePadVolumeGain* gainSettings);
int scePadTerminate(void);

#ifdef __cplusplus
}
#endif

#endif // _LIBSCEPAD_H_
