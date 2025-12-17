/** 
 * The GameCenterInterface allows users to access Game Center from iOS applications. Be sure to call GameCenterInterface.init() in your AS2 code.
 */

/**************************************************************************

Filename    :   GameCenterInterface.as

Copyright   :   Copyright 2012 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

import flash.external.ExternalInterface;

class gfx.utils.GameCenterInterface {
	static var _loginUser:Function;
	
	static var _openLeaderboardPane:Function;
	static var _setLeaderboardScore:Function;
	
	static var _openAchievementPane:Function;
	static var _setAchievementCompletion:Function;
	static var _resetAchievements:Function;
	
	static var _receiveOnlineResult:Function;

	public static function init():Void {
		ExternalInterface.call("GameCenterInterface.init", GameCenterInterface);
	}
	
	public static function loginUser():Void {
		_loginUser();
	}
	
	public static function openLeaderboardPane():Void {
		_openLeaderboardPane();
	}

	public static function setLeaderboardScore(id:String, value:Number):Void {
		_setLeaderboardScore(id, value);
	}
	
	public static function openAchievementPane():Void {
		_openAchievementPane();
	}
	public static function setAchievementCompletion(id:String, value:Number):Void {
		_setAchievementCompletion(id, value);
	}

	public static function resetAchievements():Boolean {
		return _resetAchievements();
	}

	public static function receiveOnlineResult():Boolean {
		return _receiveOnlineResult();
	}
}
