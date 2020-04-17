#version 330 core

/*
    预积分的 BRDF LUT 图
    用于IBL镜面反射部分
*/
out vec4 FragColor;
in vec2 TexCoords;

const float PI = 3.14159265359;

// 低差异随机序列生成
float RadicalInverse_VdC(uint bits) 
{
    bits = (bits << 16u) | (bits >> 16u);
    bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
    bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
    bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
    bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
    return float(bits) * 2.3283064365386963e-10; 
}

vec2 Hammersley(uint i, uint N)
{
	return vec2(float(i)/float(N), RadicalInverse_VdC(i));
}


// 重要性采样
// Xi 是输入的随机低差异序列值
// 得到的随机采样向量受到粗糙度的影响
vec3 ImportanceSampleGGX(vec2 Xi, vec3 N, float roughness)
{
    // 粗糙度参与了随机向量生成
	float a = roughness * roughness;

    // 构造球形坐标下的采样向量
	float phi = 2.0 * PI * Xi.x;

    // 注意这里： 当粗糙度从 0 - 1 递增时， cosθ 递减, sinθ递增
    // 因此采样向量 H = ( sinφsinθ , cosφsinθ, cosθ) 在粗糙度接近 0 时，也就是光滑镜面下
    // cosθ 最大，sinθ最小
    // 这时 H 与法向量 N (0,0,1) 的偏差最小 这时候采样向量 H 集中在镜面反射周围
	float cosTheta = sqrt((1.0 - Xi.y) / (1.0 + ( a*a - 1.0) * Xi.y));
	float sinTheta = sqrt(1.0 - cosTheta*cosTheta);

    //  球形坐标转换回笛卡尔坐标系
	vec3 H;
	H.x = cos(phi) * sinTheta;
	H.y = sin(phi) * sinTheta;
	H.z = cosTheta;
	
    // 构造一个切线空间正交基
	vec3 up = abs(N.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
	vec3 tangent = normalize(cross(up, N));
	vec3 bitangent = cross(N, tangent);
	
    // 得到世界空间下随机采样向量
	vec3 sampleVec = tangent * H.x + bitangent * H.y + N * H.z;

	return normalize(sampleVec);
}


// Schlick GGX 函数
// 对应 BRDF 的 G
// https://learnopengl-cn.github.io/07%20PBR/01%20Theory/
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float a = roughness;
    // ibl 的 k
    float k = (a * a) / 2.0;

    // cosθ
    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
    return nom / denom;
}

// Schlick GGX 函数仅考虑了视线
// 使用 Smith 法将光线方向也纳入 G 函数输出影响因素中
// https://learnopengl-cn.github.io/07%20PBR/01%20Theory/
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);

    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}


// NdotV 是法线与视线夹角余弦值 即cosθ
vec2 IntegrateBRDF(float NdotV, float roughness)
{
    // learnopengl上给出的代码实现
    // 更加详细的解释：
    // https://blog.selfshadow.com/publications/s2013-shading-course/karis/s2013_pbs_epic_notes_v2.pdf
    // 我把它下载到了document文件夹下了

    vec3 V;

    // sinθ
    V.x = sqrt(1.0 - NdotV*NdotV);
    V.y = 0.0;

    // cosθ
    V.z = NdotV;

    float A = 0.0;
    float B = 0.0; 

    // 这里法线方向设为 z轴向上
    // 与重要性采样时的 NDF 设置保持一致
    // 详见函数 ImportanceSampleGGX(vec2 Xi, vec3 N, float roughness) 的注解
    vec3 N = vec3(0.0, 0.0, 1.0);
    
    const uint SAMPLE_COUNT = 1024u;
    for(uint i = 0u; i < SAMPLE_COUNT; ++i)
    {
        // 生成 Hammersley 序列
        vec2 Xi = Hammersley(i, SAMPLE_COUNT);

        // 生成重要性随机采样向量
        // 世界空间下
        vec3 H = ImportanceSampleGGX(Xi, N, roughness);
        vec3 L = normalize(2.0 * dot(V, H) * H - V);
        float NdotL = max(L.z, 0.0);
        float NdotH = max(H.z, 0.0);
        float VdotH = max(dot(V, H), 0.0);

        if(NdotL > 0.0)
        {
            // BRDF G 项
            float G = GeometrySmith(N, V, L, roughness);
            float G_Vis = (G * VdotH) / (NdotH * NdotV);
            float Fc = pow(1.0 - VdotH, 5.0);
            A += (1.0 - Fc) * G_Vis;
            B += Fc * G_Vis;
        }
    }
    A /= float(SAMPLE_COUNT);
    B /= float(SAMPLE_COUNT);
    return vec2(A, B);
}

void main() 
{
    vec2 integratedBRDF = IntegrateBRDF(TexCoords.x, TexCoords.y);
    FragColor = vec4(integratedBRDF, 0.0, 1.0);
}