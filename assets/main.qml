import bb.cascades 1.0

Page {
    Container {
        Label {
            horizontalAlignment: HorizontalAlignment.Center
            text: "Rows"
        }
        Container {
            horizontalAlignment: HorizontalAlignment.Center
            verticalAlignment: VerticalAlignment.Center
            //background: Color.Black
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            }
            Container {
                ImageButton {
                    defaultImageSource: "asset:///images/stepper/minus.png"
                    pressedImageSource: "asset:///images/stepper/minus.png"
                }
            }
            Container {
                layout: DockLayout {
                
                }
                ImageView {
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Center
                    imageSource: "asset:///images/stepper/center.png"
                }
                Label {
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Center
                    text: "23"
                }
            }
            Container {
                ImageButton {
                    defaultImageSource: "asset:///images/stepper/plus.png"
                    pressedImageSource: "asset:///images/stepper/plus.png"
                }
            }
        }
    }
}
