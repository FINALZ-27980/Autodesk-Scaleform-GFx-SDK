/**************************************************************************

Filename    :   Layout_Container.as

Copyright   :   Copyright 2014 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

package com.scaleform.demos {
    import flash.display.MovieClip;
	import flash.events.Event;
    import flash.display.StageScaleMode;

    import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.events.ButtonEvent;
	
    import scaleform.clik.layout.Layout;
    import scaleform.clik.layout.LayoutData;
    
    import scaleform.gfx.Extensions;
    import flash.geom.Rectangle;

    public class Layout_Container extends UIComponent {
        
		// demo text
		public var textSprite:MovieClip;
		
		// toggles safe areas
		public var checkSprite:MovieClip;
		public var CheckBox1:CheckBox;
		
		// safe area
		public var safeSprite:MovieClip;
		
		// references to the instances on the stage
        // this will be dynamically resized and maintain aspect ratio
        public var radarSprite:MovieClip;   

        // this will not be resized at all
        public var chatSprite:MovieClip;
		
        // this will be resized 1:1 with the visibleRect; essentially covering the background
        public var backgroundSprite:MovieClip;
		
		
        // internal layout class which automates much of the resizing work.
        private var layout:Layout;

        private var OriginalStageWidth: Number;
        private var OriginalStageHeight: Number;

        function toggleSafeVisibility( event:Event ):void {
            safeSprite.visible = checkSprite.CheckBox1.selected;
        }

        override protected function configUI(): void {
            super.configUI();
            Extensions.enabled = true;
			
			safeSprite.visible = false;
			
			// Configure CheckBox1
            checkSprite.CheckBox1.label = "Toggle Safe Area";
			checkSprite.CheckBox1.addEventListener(ButtonEvent.CLICK, toggleSafeVisibility, false, 0, true);
			
            OriginalStageWidth = stage.stageWidth;
            OriginalStageHeight = stage.stageHeight;

            // If SHOW_ALL is used, all layout data enabled clips will be rescaled.
            // Using NO_SCALE, the clips maintain their original size.
            // We take advantage of this to maintain the chatWindow size and 
            // manually re-scale the radarSprite to maintain aspect ratio.

            // EXACT_FIT simply matches the dimensions of the window
            // NO_BORDER: only matches the height of the window; clips horizontal content
            stage.scaleMode = StageScaleMode.NO_SCALE;

            // initialize layout data for sprites
			textSprite.layoutData = new LayoutData();
            textSprite.layoutData.alignH = "left";
            textSprite.layoutData.alignV = "top";
            textSprite.layoutData.offsetH = 70;
            textSprite.layoutData.offsetV = 40;
			
			radarSprite.layoutData = new LayoutData();
            radarSprite.layoutData.alignV = "top";
            radarSprite.layoutData.alignH = "right";
            radarSprite.layoutData.offsetH = -10;
            radarSprite.layoutData.offsetV = 40;

            chatSprite.layoutData = new LayoutData();
            chatSprite.layoutData.alignH = "left";
            chatSprite.layoutData.alignV = "bottom";
            chatSprite.layoutData.offsetH = 70;
            chatSprite.layoutData.offsetV = -40;
			
			checkSprite.layoutData = new LayoutData();
            checkSprite.layoutData.alignH = "right";
            checkSprite.layoutData.alignV = "bottom";
            checkSprite.layoutData.offsetH = -70;
            checkSprite.layoutData.offsetV = -40;
			
            backgroundSprite.width = stage.stageWidth;
            backgroundSprite.height = stage.stageHeight;
            backgroundSprite.layoutData = new LayoutData();
            backgroundSprite.layoutData.alignH = "center";
            backgroundSprite.layoutData.alignV = "center";

            //safeSprite.layoutData = new LayoutData();
            //safeSprite.layoutData.alignH = "center";
            //safeSprite.layoutData.alignV = "center";

            // since the stage.scaleMode is NO_SCALE and we want to resize
            // the radarSprite manually, we add an event here.
            stage.addEventListener(Event.RESIZE, onResize, false, 0, true);

            var initialAspectRatio:Number = (radarSprite.width/radarSprite.height);
            trace("initialAspectRatio: " + initialAspectRatio);

            // create a new layout and tie it stage size
            layout = new Layout();
            layout.tiedToStageSize = true;
            addChild(layout);
        }


        function onResize(e:Event): void {
            // calculate ratio from new stage to old stage
            var dX:Number = (Extensions.visibleRect.width/OriginalStageWidth);
            var dY:Number = (Extensions.visibleRect.height/OriginalStageHeight);

            // apply the deviation to the radarSprite and safeSprite
            if (dX > dY)
            {
                radarSprite.scaleX = radarSprite.scaleY = dX;
				//safeSprite.scaleX = safeSprite.scaleY = dX;
            }
            else if (dY > dX)
            {
                radarSprite.scaleX = radarSprite.scaleY = dY;
				//safeSprite.scaleX = safeSprite.scaleY = dY;
            }
            else
            {
                radarSprite.scaleX = radarSprite.scaleY = 1;
				//safeSprite.scaleX = safeSprite.scaleY = 1;
            }

			
			
            // resize the background sprite to be 1:1 with the visibleRect.
            backgroundSprite.width = Extensions.visibleRect.width;
            backgroundSprite.height = Extensions.visibleRect.height;
			
            layout.reflow();

            // assert that this window has maintained the aspect ratio
            var ratio:Number = radarSprite.width / radarSprite.height;
            trace("-> updated aspect ratio: " + ratio);
			
		}
    }
}