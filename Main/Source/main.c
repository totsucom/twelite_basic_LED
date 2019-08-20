/*
 * TWELITE BLUE/RED (MONOSTICK含む) でLチカ
 * SDK バージョン 2018-05
 *
 */

#include "AppHardwareApi.h"
#include "utils.h"
#include "ToCoNet.h"

// LチカさせるDIO番号
// モノスティックの場合は16が赤色LED
// DIPの場合は基板に16と書かれているピンに1kΩ以上の抵抗とともにLEDを接続してください。(ピンの最大出力は4mAです)
// もしくは適宜ピン番号を変更してください。
#define LED  16

// ユーザ定義のイベントハンドラ
// ウィンドウズのwndProc()みたいなもん
// 比較的重めの処理を書いてもいいけどブロックしてはいけません
static void vProcessEvCore(tsEvent *pEv, teEvent eEvent, uint32 u32evarg)
{
    static bool_t b = TRUE;

    switch (eEvent) {

    // 起動時
	case E_EVENT_START_UP:
        //起動時メッセージ出力など最初にやりたいことをここに記述
        //ハードウェアの初期化はここではなくcbAppColdStart()で
        break;

    // 4ms毎タイマー
    case E_EVENT_TICK_TIMER: 
        break;

    // 1秒毎タイマー
    case E_EVENT_TICK_SECOND:

        // 1秒毎に点滅を繰り返す
        // モノスティックの場合はLoで点灯
        if (b) {
            vPortSetHi(LED);
        } else {
            vPortSetLo(LED);
        }
        b = !b;
        break;

    }
}

// 電源オンによるスタート
void cbAppColdStart(bool_t bAfterAhiInit)
{
	if (!bAfterAhiInit) {
	} else {

        // ユーザ定義のイベントハンドラを登録
        ToCoNet_Event_Register_State_Machine(vProcessEvCore);

        // IOポート初期化
        vPortAsOutput(LED);
	}
}

// スリープからの復帰
void cbAppWarmStart(bool_t bAfterAhiInit)
{
}

// ネットワークイベント発生時
void cbToCoNet_vNwkEvent(teEvent eEvent, uint32 u32arg)
{
}

// パケット受信時
void cbToCoNet_vRxEvent(tsRxDataApp *pRx)
{
}

// パケット送信完了時
void cbToCoNet_vTxEvent(uint8 u8CbId, uint8 bStatus)
{
}

// ハードウェア割り込み発生後（遅延呼び出し）
void cbToCoNet_vHwEvent(uint32 u32DeviceId, uint32 u32ItemBitmap)
{
    //割り込みに対する処理は通常ここで行う。
}

// ハードウェア割り込み発生時
uint8 cbToCoNet_u8HwInt(uint32 u32DeviceId, uint32 u32ItemBitmap)
{
    //割り込みで最初に呼ばれる。最短で返さないといけない。

    //注)ここで目的の割り込み処理を実行したときだけTRUEを返すようにすること。
    //  常にTRUEを返すと固まる!!

	return FALSE;//FALSEによりcbToCoNet_vHwEvent()が呼ばれる
}

// メイン
void cbToCoNet_vMain(void)
{
    //C言語のmain()とは動作が異なる
}
