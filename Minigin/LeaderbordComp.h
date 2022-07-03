#pragma once
#include "BaseComponent.h"
#include "Font.h"
#include "TextObject.h"

class LeaderbordComp : public BaseComponent
{
public:
	LeaderbordComp(const std::shared_ptr<dae::Font>& font, int spacing, bool visible);

	void Update(float elapsedSec) override;
	void Render(glm::vec3 pos) const override;

	void CheckPositionInLeaderbord(const std::string& name, int score);
	void Save();
	void SetVisible(bool active);

private:
	bool m_Visible;
	int m_Spacig;
	std::vector<std::pair<std::string, int>> m_Leaderbord;
	std::shared_ptr<dae::TextObject> m_pPlayer1;
	std::shared_ptr<dae::TextObject> m_pPlayer2;
	std::shared_ptr<dae::TextObject> m_pPlayer3;
	std::shared_ptr<dae::TextObject> m_pPlayer4;
	std::shared_ptr<dae::TextObject> m_pPlayer5;

	void ReadFileTop5();
};

