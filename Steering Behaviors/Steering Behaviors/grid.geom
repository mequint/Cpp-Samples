#version 330
layout (points) in;
layout (line_strip, max_vertices = 3) out;

void main()
{
	gl_Position = gl_in[0].gl_Position + vec4(0.0, 0.2, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4(0.0, 0.0, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4(0.2, 0.0, 0.0, 0.0);
	EmitVertex();
	
	EndPrimitive();
}