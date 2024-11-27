#ifndef MOUSE_RECORDER_H
#define MOUSE_RECORDER_H

#include "MouseDriver.h"

typedef unsigned long long ull;

/**
 * @brief Initiates the recording
 *
 */
void InitMouseRecorder(void);

/**
 * @brief Frees any data allocated by mouse recorder
 *
 */
void DisposeMouseRecorder(void);

/**
 * @brief Adjusts the position of the mouse to fit in window screen after all
 * data has been recorded
 *
 */
void AdjustPositionsBeforeExit(void);

/**
 * @brief Records the positions of the mouse into a position.dat file
 *
 * @param driver
 */
void RecordPoisitions(MouseDriver* driver);

/**
 * @brief Packs two 32 bit integers into one 64 bit long
 *
 * @param x
 * @param y
 * @return ull
 */
ull Pack(int x, int y);

/**
 * @brief Unpacks 64 bit number into 2 32 bit integerss
 *
 * @param packed
 * @param x
 * @param y
 */
void Unpack(ull packed, int* x, int* y);

#endif  // MOUSE_RECORDER_H