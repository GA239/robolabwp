attribute vec4 positionCoords;
attribute vec2 textureCoords;

varying lowp vec4 color;
uniform mat4 modelViewProjectionMatrix;
uniform vec3 rgbColor;
uniform mat2 alphaValues;


void main()
{
    float alphaValue;
    gl_Position = modelViewProjectionMatrix * positionCoords;
    
    alphaValue = alphaValues[int(textureCoords.x)][int(textureCoords.y)];
    
    color = vec4(rgbColor, alphaValue);
}