attribute vec4 positionCoords;
attribute vec2 textureCoords;


varying lowp vec4 color;
varying highp vec2 texCoord;
uniform mat4 modelViewProjectionMatrix;
uniform vec3 rgbColor;
uniform mat2 alphaValues;

void main()
{
    float alphaValue;
    gl_Position = modelViewProjectionMatrix * positionCoords;
    alphaValue = alphaValues[int(positionCoords.x)][int(positionCoords.y)];
    color = vec4(1.0, 1.0, 1.0, alphaValue);
    texCoord = textureCoords;
}