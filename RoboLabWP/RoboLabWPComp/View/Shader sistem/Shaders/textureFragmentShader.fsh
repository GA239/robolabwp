uniform lowp sampler2D sampler;
varying lowp vec4 color;
varying highp vec2 texCoord;

void main()
{
    gl_FragColor = color * texture2D(sampler, texCoord);
}