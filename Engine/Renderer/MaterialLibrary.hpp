#ifndef ENGINE_MATERIAL_LIBRARY_HPP
#define ENGINE_MATERIAL_LIBRARY_HPP

#include <map>
#include <vector>


namespace Engine
{
	class Material;
	class Shader;
	class RenderTarget;

	class MaterialLibrary
	{
	private:
		std::map<unsigned int, Material*> m_DefaultMaterials;
		std::vector<Material*> m_Materials;

		Material* defaultBlitMaterial;

		Shader* deferredAmbientShader;
		Shader* deferredIrradianceShader;
		Shader* deferredDirectionalShader;
		Shader* deferredPointShader;

		Shader *dirShadowShader;

		Material *debugLightMaterial;
	public:
		MaterialLibrary(RenderTarget *gBuffer);
		~MaterialLibrary();

		Material* CreateMaterial(std::string base);             
		Material* CreateCustomMaterial(Shader *shader);         
		Material* CreatePostProcessingMaterial(Shader *shader);

	private:
		void GenerateDefaultMaterials();
		void GenerateInternalMaterials(RenderTarget *gBuffer);
	};
}



#endif // !ENGINE_MATERIAL_LIBRARY_HPP
