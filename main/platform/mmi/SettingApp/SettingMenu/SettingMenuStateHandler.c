/*==============================================================================
// 文件：
//        SettingMenuStateHandler.c
//        版权所有(c) 2009 Anylook Tech. CO.,LTD.
//
// 文件说明：
//
// 作者：Gemsea
// 创建日期：2007-11-01
// 当前版本：Draft
==============================================================================*/

/*==============================================================================
修改历史记录：
时       间      修 改 人    问题单号  修改内容、位置及原因
-----------      ----------  --------  -----------------------------------------
==============================================================================*/


/*==============================================================================
                                 本文件包含的外部文件
==============================================================================*/
#include "SettingMenu_priv.h"

/*==============================================================================
                                 宏定义和常数
==============================================================================*/


/*==============================================================================
                                 类型定义
==============================================================================*/


/*==============================================================================
                                 函数声明
==============================================================================*/
// 状态 SETTINGMENUST_NONE 处理函数
static NextFSMAction SettingMenu_StateNoOperationHandler(CSettingMenu *pMe);

// 状态 SETTINGMENUST_INIT 处理函数
static NextFSMAction SettingMenu_StateInitHandler(CSettingMenu *pMe);

// 状态 SETTINGMENUST_MAIN 处理函数
static NextFSMAction SettingMenu_StateMainHandler(CSettingMenu *pMe);

// 状态 SETTINGMENUST_CALLSETTING 处理函数
static NextFSMAction SettingMenu_StateCallSettingHandler(CSettingMenu *pMe);

// 状态 SETTINGMENUST_PHONESETTING 处理函数
static NextFSMAction SettingMenu_StatePhoneSettingHandler(CSettingMenu *pMe);

// 状态 SETTINGMENUST_CALLSETTINGSEL 处理函数
static NextFSMAction SettingMenu_StateCallSettingSelHandler(CSettingMenu *pMe);

// 状态 SETTINGMENUST_NETWORKSETTING 处理函数
static NextFSMAction SettingMenu_StateNetworkSettingHandler(CSettingMenu *pMe);

// 状态 SETTINGMENUST_DIVERT 处理函数
static NextFSMAction SettingMenu_StateDivertHandler(CSettingMenu *pMe);

// 状态 SETTINGMENUST_CALLFORWARDSEL 处理函数
static NextFSMAction SettingMenu_StateCallForwardSelHandler(CSettingMenu *pMe);

// 状态 SETTINGMENUST_CALLFORWARDINPUT 处理函数
static NextFSMAction SettingMenu_StateCallForwardInputHandler(CSettingMenu *pMe);
#ifdef FEATURE_KEYGUARD
// 状态 SETTINGMENUST_AKG 处理函数
static NextFSMAction SettingMenu_StateAKGHandler(CSettingMenu *pMe);
#endif

#ifdef FEATURE_SET_BANNER
// 状态 SETTINGMENUST_BANNER 处理函数
static NextFSMAction SettingMenu_StateBannerHandler(CSettingMenu *pMe);
#endif

#ifdef FEATURE_TIME_DATA_SETTING
// 状态 TIMESETTING 处理函数
static NextFSMAction SettingMenu_StateTimeHandler(CSettingMenu *pMe);

// 状态 dateSETTING 处理函数
static NextFSMAction SettingMenu_StateDateHandler(CSettingMenu *pMe);
#endif
// 状态 SETTINGMENUST_LANGUAGE 处理函数
static NextFSMAction SettingMenu_StateLanguageHandler(CSettingMenu *pMe);

// 状态 SETTINGMENUST_EXIT 处理函数
static NextFSMAction SettingMenu_StateExitHandler(CSettingMenu *pMe);

#ifdef FEATURE_PERU_VERSION
static NextFSMAction SettingMenu_StatePhoneNumerHandler(CSettingMenu *pMe);
#endif
#ifdef FEATURE_SID_LOCK
static NextFSMAction SettingMenu_StateNetSelectHandler(CSettingMenu *pMe);
#endif

#ifdef FEATRUE_AUTO_POWER
static NextFSMAction SettingMenu_StateAutoPowerHandler(CSettingMenu *pMe);
#endif
#ifdef FEATURE_SUPPORT_G_SENSOR
static NextFSMAction SettingMenu_StateShake(CSettingMenu *pMe);

static NextFSMAction SettingMenu_StateShakeSub(CSettingMenu *pMe);
#endif
static NextFSMAction SettingMenu_StatePasswordHandler(CSettingMenu *pMe); 

static NextFSMAction SettingMenu_StateCallRestrictHandler(CSettingMenu *pMe); 

static NextFSMAction SettingMenu_StateOutGoingHandler(CSettingMenu *pMe); 

static NextFSMAction SettingMenu_StateIncomingHandler(CSettingMenu *pMe);

static NextFSMAction SettingMenu_StateAutoAnswer_Mode(CSettingMenu *pMe);

#ifdef FEATRUE_SET_IP_NUMBER
static NextFSMAction SettingMenu_StateIP_Number_Set_Mode(CSettingMenu *pMe);
#endif
// 状态 DLGRET_KEYLENGTH 处理函数
static NextFSMAction Sound_StateKeylengthHandler(CSettingMenu *pMe);

static NextFSMAction Sound_StateAutoAnswerSubHandler(CSettingMenu *pMe);
#ifdef FEATURE_PLANEMODE
static NextFSMAction SettingMenu_StatePlaneModeHandler(CSettingMenu *pMe);
#endif

/*==============================================================================
                                 全局数据
==============================================================================*/


/*==============================================================================
                                 本地（静态）数据
==============================================================================*/


/*==============================================================================
                                 函数定义
==============================================================================*/
/*==============================================================================
函数:
       SettingMenu_ProcessState
说明:
       SettingMenu Applet状态处理主函数。函数根据pMe->m_currState将调用路由至
       相应的处理函数。

参数:
       pMe [In]: 指向SettingMenu Applet对象结构的指针,该结构包含小程序的特定信息.

返回值:
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注:

==============================================================================*/
NextFSMAction SettingMenu_ProcessState(CSettingMenu *pMe)
{
    NextFSMAction retVal = NFSMACTION_WAIT;

    if (NULL == pMe)
    {
        return retVal;
    }

    // 根据当前状态调用相应的状态处理函数
    switch (pMe->m_eCurState)
    {
        case SETTINGMENUST_NONE:
            retVal = SettingMenu_StateNoOperationHandler(pMe);
            break;

        case SETTINGMENUST_INIT:
            retVal = SettingMenu_StateInitHandler(pMe);
            break;

        case SETTINGMENUST_MAIN:
            retVal = SettingMenu_StateMainHandler(pMe);
            break;

        case SETTINGMENUST_CALLSETTING:
            retVal = SettingMenu_StateCallSettingHandler(pMe);
            break;

        case SETTINGMENUST_PHONESETTING:
            retVal = SettingMenu_StatePhoneSettingHandler(pMe);
            break;

        case SETTINGMENUST_CALLSETTINGSEL:
            retVal = SettingMenu_StateCallSettingSelHandler(pMe);
            break;

        case SETTINGMENUST_NETWORKSETTING:
            retVal = SettingMenu_StateNetworkSettingHandler(pMe);
            break;

        case SETTINGMENUST_DIVERT:
            retVal = SettingMenu_StateDivertHandler(pMe);
            break;

        case SETTINGMENUST_CALLFORWARDSEL:
            retVal = SettingMenu_StateCallForwardSelHandler(pMe);
            break;

        case SETTINGMENUST_CALLFORWARDINPUT:
            retVal = SettingMenu_StateCallForwardInputHandler(pMe);
            break;
#ifdef FEATURE_KEYGUARD
        case SETTINGMENUST_AKG:
            retVal = SettingMenu_StateAKGHandler(pMe);
            break;
#endif

#ifdef FEATURE_SET_BANNER
        case SETTINGMENUST_BANNER:
            retVal = SettingMenu_StateBannerHandler(pMe);
            break;
#endif

#ifdef FEATURE_TIME_DATA_SETTING
        case SETTINGMENUST_TIMESETTING:
            retVal = SettingMenu_StateTimeHandler(pMe);
            break;

        case SETTINGMENUST_DATESETTING:
            retVal = SettingMenu_StateDateHandler(pMe);
            break;
#endif
        case SETTINGMENUST_LANGUAGE:
            retVal = SettingMenu_StateLanguageHandler(pMe);
            break;

        case SETTINGMENUST_EXIT:
            retVal = SettingMenu_StateExitHandler(pMe);
            break;

#ifdef FEATURE_PERU_VERSION
        case SETTINGMENUST_PHONENUMBER:
            retVal = SettingMenu_StatePhoneNumerHandler(pMe);
            break;
#endif
#ifdef FEATURE_SID_LOCK
        case SETTINGMENUST_NETSELECT:
            retVal = SettingMenu_StateNetSelectHandler(pMe);
            break;
#endif    //FEATURE_NETWORK_SET
#ifdef FEATRUE_AUTO_POWER
        case SETTINGMENUST_AUTO_POWER:
            retVal = SettingMenu_StateAutoPowerHandler(pMe);
            break;
#endif
#ifdef FEATURE_SUPPORT_G_SENSOR
        case SETTINGMENUST_SHAKE:
            retVal = SettingMenu_StateShake(pMe);
            break;

        case SETTINGMENUST_SHAKESUB:
            retVal = SettingMenu_StateShakeSub(pMe);
            break;
#endif
        case SETTINGMENUST_PASSWORD:
            retVal = SettingMenu_StatePasswordHandler(pMe);
            break;
            
        case SETTINGMENUST_CALLRESTRICT:
            retVal = SettingMenu_StateCallRestrictHandler(pMe);
            break;
            
        case SETTINGMENUST_RESTRICTOUTGOING:
            retVal = SettingMenu_StateOutGoingHandler(pMe);
            break;
        
        case SETTINGMENUST_RESTRICTINCOMING:
            retVal = SettingMenu_StateIncomingHandler(pMe);
            break;
        case SETTINGMENUST_AUTO_ANSWER:
            retVal = SettingMenu_StateAutoAnswer_Mode(pMe);
            break;

#ifdef FEATRUE_SET_IP_NUMBER
        case SETTINGMENUST_IP_NUMBER_SET:
            retVal = SettingMenu_StateIP_Number_Set_Mode(pMe);
            break;
#endif
        case SETTINGMENUST_KEYLENGTH:
            retVal = Sound_StateKeylengthHandler(pMe);
            break;

        case SETTINGMENUST_AUTOANSWERSUB:
            retVal = Sound_StateAutoAnswerSubHandler(pMe);
            break;

#ifdef FEATURE_PLANEMODE
        case SETTINGMENUST_PLANEMODE:
            retVal = SettingMenu_StatePlaneModeHandler(pMe);
            break; 
#endif
        default:
            ASSERT_NOT_REACHABLE;
    }
    SETTING_ERR("curstate %d prestate %d dlgret %d CallApp_ProcessState",pMe->m_eCurState,pMe->m_ePreState,pMe->m_eDlgRet);
    return retVal;
}


/*==============================================================================
函数：
       StateNoOperationHandler
说明：
       SETTINGMENUST_NONE 状态处理函数

参数：
       pMe [in]：指向SettingMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
static NextFSMAction SettingMenu_StateNoOperationHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    MOVE_TO_STATE(SETTINGMENUST_EXIT)
    return NFSMACTION_CONTINUE;
} // StateNoOperationHandler


/*==============================================================================
函数：
       StateInitHandler
说明：
       SETTINGMENUST_INIT 状态处理函数

参数：
       pMe [in]：指向SettingMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
static NextFSMAction SettingMenu_StateInitHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    MOVE_TO_STATE(SETTINGMENUST_MAIN)
    return NFSMACTION_CONTINUE;
} // StateInitHandler


/*==============================================================================
函数：
       StateMainHandler
说明：
       SETTINGMENUST_MAIN 状态处理函数

参数：
       pMe [in]：指向SettingMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
static NextFSMAction SettingMenu_StateMainHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    pMe->m_nSubDlgId = 0 ;    //重新计算子菜单选择条的位置

    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            SettingMenu_ShowDialog(pMe, IDD_MAIN_MENU);
            return NFSMACTION_WAIT;

        case DLGRET_PHONESETTING:
            MOVE_TO_STATE(SETTINGMENUST_PHONESETTING)
            return NFSMACTION_CONTINUE;

        case DLGRET_CALLSETTING:
            MOVE_TO_STATE(SETTINGMENUST_CALLSETTING)
            return NFSMACTION_CONTINUE;

#ifdef FEATURE_PERU_VERSION
        case DLGRET_PHONE_NUMBER:
            MOVE_TO_STATE(SETTINGMENUST_PHONENUMBER)
            return NFSMACTION_CONTINUE;
#endif
#ifdef FEATURE_SID_LOCK
        case DLGRET_NET_SELECT:
            MOVE_TO_STATE(SETTINGMENUST_NETSELECT)
            return NFSMACTION_CONTINUE;
#endif   //FEATURE_NETWORK_SET

#ifdef FEATRUE_AUTO_POWER
         case DLGRET_AUTO_POWER:
            MOVE_TO_STATE(SETTINGMENUST_AUTO_POWER)
            return NFSMACTION_CONTINUE;
#endif
#ifdef FEATURE_SUPPORT_G_SENSOR
        case DLGRET_SHAKE:
            MOVE_TO_STATE(SETTINGMENUST_SHAKE)
            return NFSMACTION_CONTINUE;
#endif
        case DLGRET_CANCELED:
            MOVE_TO_STATE(SETTINGMENUST_EXIT)
            return NFSMACTION_CONTINUE;

        default:
            ASSERT_NOT_REACHABLE;
    }

    return NFSMACTION_WAIT;
} // StateMainHandler


/*==============================================================================
函数：
       StateCallSettingHandler
说明：
       SETTINGMENUST_CALLSETTING 状态处理函数

参数：
       pMe [in]：指向SettingMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
static NextFSMAction SettingMenu_StateCallSettingHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            SettingMenu_ShowDialog(pMe, IDD_CALLSETTING_MENU);
            return NFSMACTION_WAIT;

        case DLGRET_CALLSETTINGSEL:
            MOVE_TO_STATE(SETTINGMENUST_CALLSETTINGSEL)
            return NFSMACTION_CONTINUE;

        case DLGRET_NETWORKSETTING:
            MOVE_TO_STATE(SETTINGMENUST_NETWORKSETTING)
            return NFSMACTION_CONTINUE;
            
        case DLGRET_DIVERT:
            MOVE_TO_STATE(SETTINGMENUST_DIVERT)
            return NFSMACTION_CONTINUE;
            
        case DLGRET_CALLFORWARDSEL:
            MOVE_TO_STATE(SETTINGMENUST_CALLFORWARDSEL)
            return NFSMACTION_CONTINUE;

        case DLGRET_AUTO_ANSWER_MODE:
            MOVE_TO_STATE(SETTINGMENUST_AUTO_ANSWER)
            return NFSMACTION_CONTINUE;
            
#ifdef FEATURE_CARRIER_THAILAND_HUTCH              
        case DLGRET_AUTO_ANSWER_MODE_SUB:
            MOVE_TO_STATE(SETTINGMENUST_AUTOANSWERSUB)
            return NFSMACTION_CONTINUE;
#endif //#if defined FEATURE_CARRIER_THAILAND_HUTCH  
        
        case DLGRET_PASSWORD:
        	MOVE_TO_STATE(SETTINGMENUST_PASSWORD)
        	return NFSMACTION_CONTINUE;           
            
        case DLGRET_CALLFORWARDINPUT:
            MOVE_TO_STATE(SETTINGMENUST_CALLFORWARDINPUT)
            return NFSMACTION_CONTINUE;

        case DLGRET_CANCELED:
            MOVE_TO_STATE(SETTINGMENUST_MAIN)
            return NFSMACTION_CONTINUE;
#ifdef FEATRUE_SET_IP_NUMBER
        case DLGRET_IP_NUMBER_SET:
            MOVE_TO_STATE(SETTINGMENUST_IP_NUMBER_SET)
            return NFSMACTION_CONTINUE;
#endif//#ifdef FEATRUE_SET_IP_NUMBER

        case DLGRET_KEYLENGTH:
            MOVE_TO_STATE(SETTINGMENUST_KEYLENGTH)
            return NFSMACTION_CONTINUE;
        default:
            ASSERT_NOT_REACHABLE;
    }

    return NFSMACTION_WAIT;
} // StateCallSettingHandler


/*==============================================================================
函数：
       StatePhoneSettingHandler
说明：
       SETTINGMENUST_PHONETTING 状态处理函数

参数：
       pMe [in]：指向SettingMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
static NextFSMAction SettingMenu_StatePhoneSettingHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            SettingMenu_ShowDialog(pMe, IDD_PHONESETTING_MENU);
            return NFSMACTION_WAIT;

#ifdef FEATURE_PLANEMODE
        case DLGRET_PLANEMODE:
            MOVE_TO_STATE(SETTINGMENUST_PLANEMODE)
            return NFSMACTION_CONTINUE;
#endif
        case DLGRET_LANGUAGE:
            MOVE_TO_STATE(SETTINGMENUST_LANGUAGE)
            return NFSMACTION_CONTINUE;
#ifdef FEATURE_KEYGUARD
        case DLGRET_AKG:
            MOVE_TO_STATE(SETTINGMENUST_AKG)
            return NFSMACTION_CONTINUE;
#endif

#ifdef FEATURE_SET_BANNER
        case DLGRET_BANNER:
            MOVE_TO_STATE(SETTINGMENUST_BANNER)
            return NFSMACTION_CONTINUE;
#endif

        #ifdef FEATURE_TIME_DATA_SETTING
        case DLGRET_TIMESETTING:
            MOVE_TO_STATE(SETTINGMENUST_TIMESETTING)
            return NFSMACTION_CONTINUE;

        case DLGRET_DATESETTING:
            MOVE_TO_STATE(SETTINGMENUST_DATESETTING)
            return NFSMACTION_CONTINUE;
         #endif
        case DLGRET_CANCELED:
            MOVE_TO_STATE(SETTINGMENUST_MAIN)
            return NFSMACTION_CONTINUE;

        default:
            ASSERT_NOT_REACHABLE;
    }

    return NFSMACTION_WAIT;
} // StatePhoneSettingHandler


/*==============================================================================
函数：
       StateCallSettingSelHandler
说明：
       SETTINGMENUST_CALLSETTINGSEL 状态处理函数

参数：
       pMe [in]：指向SettingMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
static NextFSMAction SettingMenu_StateCallSettingSelHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            SettingMenu_ShowDialog(pMe, IDD_CALLSETTINGSEL);
            return NFSMACTION_WAIT;

#ifdef FEATRUE_SET_IP_NUMBER
        case DLGRET_CALLFORWARDINPUT:
            MOVE_TO_STATE(SETTINGMENUST_CALLFORWARDINPUT)
            return NFSMACTION_CONTINUE;
#endif//#ifdef FEATRUE_SET_IP_NUMBER
#ifdef FEATRUE_AUTO_POWER
        case DLGRET_CALLSETTING:
            MOVE_TO_STATE(SETTINGMENUST_MAIN)
            return NFSMACTION_CONTINUE;
#endif //#ifdef FEATRUE_AUTO_POWER
        case DLGRET_CANCELED:
        case DLGRET_MSGBOX_OK:    
            if(pMe->m_CallSettingSel == IDS_ANYKEY_ANSWER_TITLE
                ||pMe->m_CallSettingSel == IDS_COVER_ANSWER
                ||pMe->m_CallSettingSel == IDS_SEND_ANSWER
                ||pMe->m_CallSettingSel == IDS_HEADSET_ANSWER
                )
            {
                MOVE_TO_STATE(SETTINGMENUST_AUTO_ANSWER)
            }
#ifdef FEATRUE_SET_IP_NUMBER
            else if(pMe->m_CallSettingSel == IDS_SET_IP_CALL_OPTION)
            {
                MOVE_TO_STATE(SETTINGMENUST_IP_NUMBER_SET)
            }
#endif//#ifdef FEATRUE_SET_IP_NUMBER
#ifdef FEATRUE_AUTO_POWER
            else if(pMe->m_CallSettingSel == IDS_AM_PM_SET)
            {
                MOVE_TO_STATE(SETTINGMENUST_AUTO_POWER)
            }
#endif //#ifdef FEATRUE_AUTO_POWER
#ifdef FEATURE_SID_LOCK
            else if(pMe->m_CallSettingSel == IDS_LOCALNET)
            {
                MOVE_TO_STATE(SETTINGMENUST_NETSELECT)
            }
#endif //#ifdef FEATURE_SID_LOCK

            else
            {
                MOVE_TO_STATE(SETTINGMENUST_CALLSETTING)
            }
            return NFSMACTION_CONTINUE;

        case DLGRET_WARNING:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            pMe->m_msg_id = IDS_DONE;
            SettingMenu_ShowDialog(pMe, IDD_WARNING_MESSEGE);
            return NFSMACTION_WAIT;

        case DLGRET_OK:
#ifdef FEATRUE_AUTO_POWER
            if(pMe->m_msg_id == IDS_AUTOPOWER_WARNING)
            {
                MOVE_TO_STATE(SETTINGMENUST_AUTO_POWER)
            }          
#endif  
#ifdef FEATURE_SID_LOCK            
            else
            {
                MOVE_TO_STATE(SETTINGMENUST_NETSELECT)
            }
#endif //#ifdef FEATURE_SID_LOCK 
            return NFSMACTION_CONTINUE;

        default:
            ASSERT_NOT_REACHABLE;
    }

    return NFSMACTION_WAIT;
} // StateCallSettingSelHandler


/*==============================================================================
函数：
       StateNetworkSettingHandler
说明：
       SETTINGMENUST_NETWORKSETTING 状态处理函数

参数：
       pMe [in]：指向SettingMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
static NextFSMAction SettingMenu_StateNetworkSettingHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            SettingMenu_ShowDialog(pMe, IDD_NETWORKSETTING_MENU);
            return NFSMACTION_WAIT;

        case DLGRET_DIVERT:
            MOVE_TO_STATE(SETTINGMENUST_DIVERT)
            return NFSMACTION_CONTINUE;

        case DLGRET_CALLFORWARDSEL:
            MOVE_TO_STATE(SETTINGMENUST_CALLFORWARDSEL)
            return NFSMACTION_CONTINUE;

        case DLGRET_CANCELED:
            MOVE_TO_STATE(SETTINGMENUST_CALLSETTING)
            return NFSMACTION_CONTINUE;

        default:
            ASSERT_NOT_REACHABLE;
    }

    return NFSMACTION_WAIT;
} // StateNetworkSettingHandler


/*==============================================================================
函数：
       StateDivertHandler
说明：
       SETTINGMENUST_DIVERT 状态处理函数

参数：
       pMe [in]：指向SettingMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
static NextFSMAction SettingMenu_StateDivertHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
        case DLGRET_MSGBOX_OK:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            SettingMenu_ShowDialog(pMe, IDD_DIVERT_MENU);
            return NFSMACTION_WAIT;

        case DLGRET_CALLFORWARDSEL:
            MOVE_TO_STATE(SETTINGMENUST_CALLFORWARDSEL)
            return NFSMACTION_CONTINUE;

        case DLGRET_CANCELED:
            MOVE_TO_STATE(SETTINGMENUST_CALLSETTING)
            return NFSMACTION_CONTINUE;

        case DLGRET_WARNING:
            pMe->m_msg_id = IDS_NOT_GET_FEATURE_CODE;
            SettingMenu_ShowDialog(pMe, IDD_WARNING_MESSEGE);
            return NFSMACTION_WAIT;

        default:
            ASSERT_NOT_REACHABLE;
    }

    return NFSMACTION_WAIT;
} // StateDivertHandler


/*==============================================================================
函数：
       StateCallForwardSelHandler
说明：
       SETTINGMENUST_CALLFORWARDSEL 状态处理函数

参数：
       pMe [in]：指向SettingMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
static NextFSMAction SettingMenu_StateCallForwardSelHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
        case DLGRET_MSGBOX_OK:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            SettingMenu_ShowDialog(pMe, IDD_CALLFORWARD_SEL);
            return NFSMACTION_WAIT;

        case DLGRET_CALLFORWARDINPUT:
            MOVE_TO_STATE(SETTINGMENUST_CALLFORWARDINPUT)
            return NFSMACTION_CONTINUE;

        case DLGRET_CANCELED:
            if(pMe->m_CFType == CALLFORWARD_WAIT 
#ifdef FEATURE_CARRIER_SUDAN_SUDATEL
                || pMe->m_CFType == CALLFORWARD_DND
#endif
                )
            {
                MOVE_TO_STATE(SETTINGMENUST_CALLSETTING)
            }
            else
            {
                MOVE_TO_STATE(SETTINGMENUST_DIVERT)
            }
            return NFSMACTION_CONTINUE;

        case DLGRET_WARNING:
            pMe->m_msg_id = IDS_NOT_GET_FEATURE_CODE;
            SettingMenu_ShowDialog(pMe, IDD_WARNING_MESSEGE);
            return NFSMACTION_WAIT;

        default:
            ASSERT_NOT_REACHABLE;
    }

    return NFSMACTION_WAIT;
} // StateCallForwardSelHandler


/*==============================================================================
函数：
       StateCallForwardInputHandler
说明：
       SETTINGMENUST_CALLFORWARDINPUT 状态处理函数

参数：
       pMe [in]：指向SettingMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
static NextFSMAction SettingMenu_StateCallForwardInputHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    switch(pMe->m_eDlgRet)
    {
        case DLGRET_MSGBOX_OK:
        case DLGRET_CREATE:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            SettingMenu_ShowDialog(pMe, IDD_CALLFORWARD_INPUT);
            return NFSMACTION_WAIT;

        case DLGRET_WARNING:
            pMe->m_msg_id = IDS_WARNING_MESSEGE;
            SettingMenu_ShowDialog(pMe, IDD_WARNING_MESSEGE);
            return NFSMACTION_WAIT;

        case DLGRET_CANCELED:
#ifdef FEATRUE_SET_IP_NUMBER
            if(pMe->m_input_mode == IDS_IP_NUMBER_SET)
            {
                MOVE_TO_STATE(SETTINGMENUST_IP_NUMBER_SET)
            }
            else if(pMe->m_input_mode == IDS_SET_IP_CALL_OPTION)
            {
                MOVE_TO_STATE(SETTINGMENUST_CALLSETTINGSEL)
            }
            else
#endif
            {
                MOVE_TO_STATE(SETTINGMENUST_DIVERT)
            }
            return NFSMACTION_CONTINUE;

        default:
            ASSERT_NOT_REACHABLE;
    }

    return NFSMACTION_WAIT;
} // StateCallForwardInputHandler

#ifdef FEATURE_KEYGUARD
/*==============================================================================
函数：
       StateAKGHandler
说明：
       SETTINGMENUST_AKG 状态处理函数

参数：
       pMe [in]：指向SettingMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
static NextFSMAction SettingMenu_StateAKGHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            SettingMenu_ShowDialog(pMe, IDD_AKG_MENU);
            return NFSMACTION_WAIT;

        case DLGRET_CANCELED:
        case DLGRET_MSGBOX_OK:            
            MOVE_TO_STATE(SETTINGMENUST_PHONESETTING)
            return NFSMACTION_CONTINUE;

        case DLGRET_WARNING:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            pMe->m_msg_id = IDS_DONE;
            SettingMenu_ShowDialog(pMe, IDD_WARNING_MESSEGE);
            return NFSMACTION_WAIT;

        default:
            ASSERT_NOT_REACHABLE;
    }

    return NFSMACTION_WAIT;
} // StateAKGHandler
#endif
#ifdef FEATURE_SET_BANNER
/*==============================================================================
函数：
       StateBannerHandler
说明：
       SETTINGMENUST_BANNER 状态处理函数

参数：
       pMe [in]：指向DisplayMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
static NextFSMAction SettingMenu_StateBannerHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            SettingMenu_ShowDialog(pMe, IDD_BANNER_TXT);
            return NFSMACTION_WAIT;

        case DLGRET_CANCELED:
            MOVE_TO_STATE(SETTINGMENUST_PHONESETTING)
            return NFSMACTION_CONTINUE;

        default:
            ASSERT_NOT_REACHABLE;
    }

    return NFSMACTION_WAIT;
} // StateBannerHandler
#endif
/*==============================================================================
函数：
       StateTimeHandler
说明：
       SETTINGMENUST_timesetting 状态处理函数

参数：
       pMe [in]：指向DisplayMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
#ifdef FEATURE_TIME_DATA_SETTING
static NextFSMAction SettingMenu_StateTimeHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            SettingMenu_ShowDialog(pMe, IDD_TIMESETTING);
            return NFSMACTION_WAIT;

        case DLGRET_CANCELED:
        case DLGRET_MSGBOX_OK:            
            MOVE_TO_STATE(SETTINGMENUST_PHONESETTING)
            return NFSMACTION_CONTINUE;

        case DLGRET_WARNING:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            pMe->m_msg_id = IDS_DONE;
            SettingMenu_ShowDialog(pMe, IDD_WARNING_MESSEGE);
            return NFSMACTION_WAIT;

        default:
            ASSERT_NOT_REACHABLE;
    }

    return NFSMACTION_WAIT;
} // StateTimeHandler



/*==============================================================================
函数：
       StatedateHandler
说明：
       SETTINGMENUST_datesetting 状态处理函数

参数：
       pMe [in]：指向DisplayMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
static NextFSMAction SettingMenu_StateDateHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            SettingMenu_ShowDialog(pMe, IDD_DATESETTING);
            return NFSMACTION_WAIT;

        case DLGRET_CANCELED:
        case DLGRET_MSGBOX_OK:            
            MOVE_TO_STATE(SETTINGMENUST_PHONESETTING)
            return NFSMACTION_CONTINUE;

        case DLGRET_WARNING:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            pMe->m_msg_id = IDS_DONE;
            SettingMenu_ShowDialog(pMe, IDD_WARNING_MESSEGE);
            return NFSMACTION_WAIT;

        default:
            ASSERT_NOT_REACHABLE;
    }

    return NFSMACTION_WAIT;
} // StatedateHandler

#endif

/*==============================================================================
函数：
       StateLanguageHandler
说明：
       SETTINGMENUST_LANGUAGE 状态处理函数

参数：
       pMe [in]：指向SettingMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
static NextFSMAction SettingMenu_StateLanguageHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            SettingMenu_ShowDialog(pMe, IDD_LANGUAGE_MENU);
            return NFSMACTION_WAIT;

        case DLGRET_CANCELED:
        case DLGRET_MSGBOX_OK:            
            MOVE_TO_STATE(SETTINGMENUST_PHONESETTING)
            return NFSMACTION_CONTINUE;

        case DLGRET_WARNING:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            pMe->m_msg_id = IDS_DONE;
            SettingMenu_ShowDialog(pMe, IDD_WARNING_MESSEGE);
            return NFSMACTION_WAIT;

        //case DLGRET_OK:
        //    ISHELL_CloseApplet(pMe->m_pShell, TRUE);
        //    return NFSMACTION_WAIT;
            
        default:
            ASSERT_NOT_REACHABLE;
    }

    return NFSMACTION_WAIT;
} // StateLanguageHandler


/*==============================================================================
函数：
       StateExitHandler
说明：
       SETTINGMENUST_EXIT 状态处理函数

参数：
       pMe [in]：指向SettingMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
static NextFSMAction SettingMenu_StateExitHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    (void) ISHELL_CloseApplet(pMe->m_pShell, FALSE);

    return NFSMACTION_WAIT;
} // StateExitHandler
#ifdef FEATURE_PERU_VERSION
/*==============================================================================
函数：
       StatePhoneNumerHandler
说明：
       SETTINGMENUST_PHONENUMBER 状态处理函数

参数：
       pMe [in]：指向SettingMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
static NextFSMAction SettingMenu_StatePhoneNumerHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
            SettingMenu_ShowDialog(pMe, IDD_PHONE_NUMBER);
            return NFSMACTION_WAIT;

        case DLGRET_CANCELED:
            MOVE_TO_STATE(SETTINGMENUST_MAIN)
            return NFSMACTION_CONTINUE;

        default:
            ASSERT_NOT_REACHABLE;
    }

    return NFSMACTION_WAIT;
}
#endif
#ifdef FEATURE_SID_LOCK
/*==============================================================================
函数：
       StatePhoneNumerHandler
说明：
       SETTINGMENUST_PHONENUMBER 状态处理函数

参数：
       pMe [in]：指向SettingMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
static NextFSMAction SettingMenu_StateNetSelectHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
            SettingMenu_ShowDialog(pMe, IDD_NET_SELECT);
            return NFSMACTION_WAIT;

        case DLGRET_CANCELED:
        case DLGRET_MSGBOX_OK:
            MOVE_TO_STATE(SETTINGMENUST_MAIN)
            return NFSMACTION_CONTINUE;

        case DLGRET_CALLSETTINGSEL:
            MOVE_TO_STATE(SETTINGMENUST_CALLSETTINGSEL)
            return NFSMACTION_CONTINUE;

        case DLGRET_WARNING:
            SettingMenu_ShowDialog(pMe, IDD_WARNING_MESSEGE);
            return NFSMACTION_WAIT;        

        default:
            ASSERT_NOT_REACHABLE;
    }

    return NFSMACTION_WAIT;
}
#endif  //FEATURE_PERU_VERSION
#ifdef FEATRUE_AUTO_POWER
static NextFSMAction SettingMenu_StateAutoPowerHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
            SettingMenu_ShowDialog(pMe, IDD_AUTO_POWER);
            return NFSMACTION_WAIT;

        case DLGRET_CANCELED:
            MOVE_TO_STATE(SETTINGMENUST_MAIN)
            return NFSMACTION_CONTINUE;

        case DLGRET_CALLSETTINGSEL:
            MOVE_TO_STATE(SETTINGMENUST_CALLSETTINGSEL)
            return NFSMACTION_CONTINUE;

        case DLGRET_WARNING:
            SettingMenu_ShowDialog(pMe, IDD_WARNING_MESSEGE);
            return NFSMACTION_WAIT;

        case DLGRET_MSGBOX_OK:
            if(pMe->m_msg_id == IDS_DONE)
            {
                MOVE_TO_STATE(SETTINGMENUST_MAIN)
                return NFSMACTION_CONTINUE;
            }
            else
            {
                SettingMenu_ShowDialog(pMe, IDD_AUTO_POWER);
                return NFSMACTION_WAIT;
            }

        default:
            ASSERT_NOT_REACHABLE;
    }
    return NFSMACTION_WAIT;
}
#endif
static NextFSMAction SettingMenu_StateAutoAnswer_Mode(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
            SettingMenu_ShowDialog(pMe, IDD_ANSWER_MODE);
            return NFSMACTION_WAIT;

        case DLGRET_CALLSETTINGSEL:
            MOVE_TO_STATE(SETTINGMENUST_CALLSETTINGSEL)
            return NFSMACTION_CONTINUE;

        case DLGRET_CANCELED:
        case DLGRET_MSGBOX_OK:
            MOVE_TO_STATE(SETTINGMENUST_CALLSETTING)
            return NFSMACTION_CONTINUE;

        case DLGRET_AUTO_ANSWER_MODE_SUB:
            MOVE_TO_STATE(SETTINGMENUST_AUTOANSWERSUB)
            return NFSMACTION_CONTINUE;

        case DLGRET_WARNING:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            pMe->m_msg_id = IDS_DONE;
            SettingMenu_ShowDialog(pMe, IDD_WARNING_MESSEGE);
            return NFSMACTION_WAIT;

        default:
            ASSERT_NOT_REACHABLE;
    }

    return NFSMACTION_WAIT;
}
#ifdef FEATRUE_SET_IP_NUMBER
static NextFSMAction SettingMenu_StateIP_Number_Set_Mode(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
            SettingMenu_ShowDialog(pMe, IDD_IP_NUMBER_SET);
            return NFSMACTION_WAIT;

        case DLGRET_CALLFORWARDINPUT:
            MOVE_TO_STATE(SETTINGMENUST_CALLFORWARDINPUT)
            return NFSMACTION_CONTINUE;

        case DLGRET_CANCELED:
            MOVE_TO_STATE(SETTINGMENUST_CALLSETTING)
            return NFSMACTION_CONTINUE;

        case DLGRET_CALLSETTINGSEL:
            MOVE_TO_STATE(SETTINGMENUST_CALLSETTINGSEL)
            return NFSMACTION_CONTINUE;

        default:
            ASSERT_NOT_REACHABLE;
    }

    return NFSMACTION_WAIT;
}
#endif /*FEATRUE_SET_IP_NUMBER*/

/*==============================================================================
函数：
       StateKeylengthHandler
说明：
       SOUNDMENUST_KEYLENGTH 状态处理函数

参数：
       pMe [in]：指向SoundMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
static NextFSMAction Sound_StateKeylengthHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            SettingMenu_ShowDialog(pMe, IDD_KEYTONE_LENGTH);
            return NFSMACTION_WAIT;

        case DLGRET_CANCELED:
            MOVE_TO_STATE(SETTINGMENUST_CALLSETTING)
            return NFSMACTION_CONTINUE;

        default:
            ASSERT_NOT_REACHABLE;
    }

    return NFSMACTION_WAIT;
} // StateKeylengthHandler

/*==============================================================================
函数：
       StateAutoAnswerSubHandler
说明：
       SOUNDMENUST_AUTOANSWERSUB 状态处理函数

参数：
       pMe [in]：指向SoundMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
static NextFSMAction Sound_StateAutoAnswerSubHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            SettingMenu_ShowDialog(pMe, IDD_AUTOANSWER_SUB);
            return NFSMACTION_WAIT;

        case DLGRET_CANCELED:         
#ifdef FEATURE_CARRIER_THAILAND_HUTCH               
            MOVE_TO_STATE(SETTINGMENUST_CALLSETTING)
#else            
            MOVE_TO_STATE(SETTINGMENUST_AUTO_ANSWER)   
#endif //#if defined FEATURE_CARRIER_THAILAND_HUTCH  
            return NFSMACTION_CONTINUE;

        default:
            return NFSMACTION_WAIT;
    }

    return NFSMACTION_WAIT;
} // StateAutoAnswerSubHandler
#ifdef FEATURE_SUPPORT_G_SENSOR
/*==============================================================================
函数：
       StateShake
说明：
       SETTINGMENUST_SHAKE 状态处理函数

参数：
       pMe [in]：指向SettingMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
#ifdef FEATURE_SPORTS_APP
extern boolean is_g_sportsapp_pedometer_bground_flag();
#endif
static NextFSMAction SettingMenu_StateShake(CSettingMenu *pMe)
{
#ifdef FEATURE_SPORTS_APP

    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }
    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:    
        {
            if(is_g_sportsapp_pedometer_bground_flag())
            {
                pMe->m_msg_id = IDS_PROCCESS;
                SettingMenu_ShowDialog(pMe, IDD_WARNING_MESSEGE);
            }
            else
            {
                SettingMenu_ShowDialog(pMe, IDD_SHAKE);
            }
            return NFSMACTION_WAIT;
        }
        case DLGRET_CANCELED:
        case DLGRET_MSGBOX_OK:
            MOVE_TO_STATE(SETTINGMENUST_MAIN)
            return NFSMACTION_CONTINUE;

        case DLGRET_SHAKESUB:
            MOVE_TO_STATE(SETTINGMENUST_SHAKESUB)
            return NFSMACTION_CONTINUE;
        case DLGRET_WARNING:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            pMe->m_msg_id = IDS_PROCCESS;
            SettingMenu_ShowDialog(pMe, IDD_WARNING_MESSEGE);
            return NFSMACTION_WAIT;    
        default:
            ASSERT_NOT_REACHABLE;
    }
#endif    
    return NFSMACTION_WAIT;	     

}

/*==============================================================================
函数：
       StateShakeSub
说明：
       SETTINGMENUST_SHAKESUB状态处理函数

参数：
       pMe [in]：指向SettingMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/

static NextFSMAction SettingMenu_StateShakeSub(CSettingMenu *pMe)
{

    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }
    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:    
            SettingMenu_ShowDialog(pMe, IDD_SHAKESUB);
            return NFSMACTION_WAIT;
            
        case DLGRET_CANCELED:
        case DLGRET_MSGBOX_OK:
            MOVE_TO_STATE(SETTINGMENUST_SHAKE)
            return NFSMACTION_CONTINUE;
        case DLGRET_WARNING:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            pMe->m_msg_id = IDS_DONE;
            SettingMenu_ShowDialog(pMe, IDD_WARNING_MESSEGE);
            return NFSMACTION_WAIT;
            
        default:
            ASSERT_NOT_REACHABLE;
    }
    return NFSMACTION_WAIT;	     

}
#endif //#ifdef FEATURE_SUPPORT_G_SENSOR
/*==============================================================================
函数：
       SettingMenu_StateCallRestrictHandler
说明：
       SETTINGMENUST_CallRestrict状态处理函数

参数：
       pMe [in]：指向SettingMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/ 
static NextFSMAction SettingMenu_StateCallRestrictHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }
    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            SettingMenu_ShowDialog(pMe, IDD_RESTRICT);
            return NFSMACTION_WAIT;

        case DLGRET_RESTRICTOUTGOING:
            MOVE_TO_STATE(SETTINGMENUST_RESTRICTOUTGOING)
            return NFSMACTION_CONTINUE;

        case DLGRET_RESTRICTINCOMING:
            MOVE_TO_STATE(SETTINGMENUST_RESTRICTINCOMING)
            return NFSMACTION_CONTINUE;

        case DLGRET_CANCELED:
            MOVE_TO_STATE(SETTINGMENUST_CALLSETTING)
            return NFSMACTION_CONTINUE;

        default:
            ASSERT_NOT_REACHABLE;
    }

    return NFSMACTION_WAIT;
} // StateRestrictHandler

/*==============================================================================
函数：
       SettingMenu_StateOutGoingHandler
说明：
       SETTINGMENUST_OutGoing状态处理函数

参数：
       pMe [in]：指向SettingMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/ 
static NextFSMAction SettingMenu_StateOutGoingHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }
    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            SettingMenu_ShowDialog(pMe, IDD_RESTRICT_OUTGOING);
            return NFSMACTION_WAIT;

        case DLGRET_CANCELED:
        case DLGRET_MSGBOX_OK:            
            MOVE_TO_STATE(SETTINGMENUST_CALLRESTRICT)
            return NFSMACTION_CONTINUE;

        case DLGRET_WARNING:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            pMe->m_msg_id = IDS_DONE;
            SettingMenu_ShowDialog(pMe, IDD_WARNING_MESSEGE);
            return NFSMACTION_WAIT;

        default:
            ASSERT_NOT_REACHABLE;
    }

    return NFSMACTION_WAIT;
}

/*==============================================================================
函数：
       SettingMenu_StateIncomingHandler
说明：
       SETTINGMENUST_Incoming状态处理函数

参数：
       pMe [in]：指向SettingMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
static NextFSMAction SettingMenu_StateIncomingHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }
    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            SettingMenu_ShowDialog(pMe, IDD_RESTRICT_INCOMING);
            return NFSMACTION_WAIT;

        case DLGRET_CANCELED:
        case DLGRET_MSGBOX_OK:            
            MOVE_TO_STATE(SETTINGMENUST_CALLRESTRICT)
            return NFSMACTION_CONTINUE;

        case DLGRET_WARNING:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            pMe->m_msg_id = IDS_DONE;
            SettingMenu_ShowDialog(pMe, IDD_WARNING_MESSEGE);
            return NFSMACTION_WAIT;

        default:
            ASSERT_NOT_REACHABLE;
    }

    return NFSMACTION_WAIT;
}
/*==============================================================================
函数：
       SettingMenu_StatePasswordHandler
说明：
       SETTINGMENUST_PASSWORD状态处理函数

参数：
       pMe [in]：指向SettingMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
static NextFSMAction SettingMenu_StatePasswordHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            SettingMenu_ShowDialog(pMe, IDD_PASSWORD);
            return NFSMACTION_WAIT;
            
        case DLGRET_INVALID:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            SettingMenu_ShowDialog(pMe,IDD_MSGBOX);
            return NFSMACTION_WAIT;
            
        case DLGRET_OK:
            MOVE_TO_STATE(SETTINGMENUST_CALLRESTRICT)
            return NFSMACTION_CONTINUE;
            
        case DLGRET_MSGBOX_OK:
            MOVE_TO_STATE(SETTINGMENUST_PASSWORD)
            return NFSMACTION_CONTINUE;

        case DLGRET_MSGBOX_CANCEL:
            MOVE_TO_STATE(SETTINGMENUST_CALLSETTING)
            return NFSMACTION_CONTINUE;
        
        case DLGRET_CANCELED:
            MOVE_TO_STATE(SETTINGMENUST_CALLSETTING)
            return NFSMACTION_CONTINUE;

        default:
        break;
    }

    return NFSMACTION_WAIT;
} // StatePasswordHandler
        	
#ifdef FEATURE_PLANEMODE
/*==============================================================================
函数：
       SettingMenu_StatePlaneModeHandler
说明：
       SETTINGMENUST_PLANEMODE 状态处理函数

参数：
       pMe [in]：指向DisplayMenu Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       NFSMACTION_CONTINUE：指示后有子状态，状态机不能停止。
       NFSMACTION_WAIT：指示因要显示对话框界面给用户，应挂起状态机。

备注：

==============================================================================*/
static NextFSMAction SettingMenu_StatePlaneModeHandler(CSettingMenu *pMe)
{
    if (NULL == pMe)
    {
        return NFSMACTION_WAIT;
    }

    switch(pMe->m_eDlgRet)
    {
        case DLGRET_CREATE:
            pMe->m_bNotOverwriteDlgRet = FALSE;
            SettingMenu_ShowDialog(pMe, IDD_PLANEMODE);
            return NFSMACTION_WAIT;

        case DLGRET_CANCELED:
        case DLGRET_MSGBOX_OK:            
            MOVE_TO_STATE(SETTINGMENUST_PHONESETTING)
            return NFSMACTION_CONTINUE;

        case DLGRET_WARNING:
            
            pMe->m_bNotOverwriteDlgRet = FALSE;
            pMe->m_msg_id = IDS_DONE;
            SettingMenu_ShowDialog(pMe, IDD_WARNING_MESSEGE);
            return NFSMACTION_WAIT;

        default:
            ASSERT_NOT_REACHABLE;
    }

    return NFSMACTION_WAIT;
} // SettingMenu_StatePlaneModeHandler
#endif 

