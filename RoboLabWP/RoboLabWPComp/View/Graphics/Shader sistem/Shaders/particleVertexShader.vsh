attribute vec4 startingPosition;
attribute vec4 properties;

uniform int currentFrame;
uniform mat4 modelViewProjectionMatrix;
uniform vec3 rgbColor;
varying lowp vec4 color;

void main()
{
    vec2 position;
    float flowLength = startingPosition.z;
    float alphaValue = properties[2];
    float xSpeed = properties[0];
    float ySpeed = properties[1];
    float initialShift = properties[3];
    float Xshift = ((float(currentFrame) + initialShift) * xSpeed) / flowLength;
    float Yshift = ((float(currentFrame) + initialShift) * ySpeed) / flowLength;
    Xshift -= float(int(((float(currentFrame) + initialShift) * xSpeed)) / int(flowLength));
    Yshift -= float(int(((float(currentFrame) + initialShift) * ySpeed)) / int(flowLength));
    Xshift *= flowLength;
    Yshift *= flowLength;
    
    position.x = startingPosition.x + Xshift;
    position.y = startingPosition.y + Yshift;
   
    gl_Position = modelViewProjectionMatrix *  vec4(position, 0.0, 1.0);
    color = vec4(rgbColor, alphaValue);
    gl_PointSize = 2.0;
}