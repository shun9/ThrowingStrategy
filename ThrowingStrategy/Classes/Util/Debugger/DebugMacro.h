//************************************************/
//* @file  :DebugMacro.h
//* @brief :�f�o�b�O�p�}�N����`
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#pragma once

//�f�o�b�O�p �R�����g��on/off�Ő؂�ւ�
//#define DEBUG


//�f�o�b�O�p�̋L�q�Ɏg�p
//Debug�̌�ɋL�q���邱�Ƃ�on/off���ꊇ�ؑ�
#ifdef DEBUG
#define Debug
#else
#define Debug 1 ? (void)0 :
#endif
