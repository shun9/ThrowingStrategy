//************************************************/
//* @file  :DebugMacro.h
//* @brief :デバッグ用マクロ定義
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#pragma once

//デバッグ用 コメントのon/offで切り替え
//#define DEBUG


//デバッグ用の記述に使用
//Debugの後に記述することでon/offを一括切替
#ifdef DEBUG
#define Debug
#else
#define Debug 1 ? (void)0 :
#endif
