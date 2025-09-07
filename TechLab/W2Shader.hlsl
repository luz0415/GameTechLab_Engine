
cbuffer constants : register(b0)
{
    row_major matrix Model;
}

cbuffer constants : register(b1)
{
    row_major matrix View;
    row_major matrix Projection;
}

struct VS_INPUT
{
    float4 position : POSITION; // Input position from vertex buffer
    float4 color : COLOR; // Input color from vertex buffer
};

struct PS_INPUT
{
    float4 position : SV_POSITION; // Transformed position to pass to the pixel shader
    float4 color : COLOR; // Color to pass to the pixel shader
};

PS_INPUT mainVS(VS_INPUT input)
{
    PS_INPUT output;
    
    // Pass the position directly to the pixel shader (no transformation)
    //output.position = input.position + float4(Offset, 0); //
    float4 position = float4(input.position.xyz, 1.0);
    float4 worldposition = mul(position, Model);
    float4 viewposition = mul(worldposition, View);
    float4 projposition = mul(viewposition, Projection);
    output.position = projposition;
    //float4(Radius, 0);
    
    // Pass the color to the pixel shader
    output.color = input.color;
    
    return output;
}

float4 mainPS(PS_INPUT input) : SV_TARGET
{
    // Output the color directly
    return input.color;
}
