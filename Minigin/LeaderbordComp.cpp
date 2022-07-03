#include "MiniginPCH.h"
#include <fstream>
#include <string>
#include <iostream>
#include "LeaderbordComp.h"

LeaderbordComp::LeaderbordComp(const std::shared_ptr<dae::Font>& font, int spacing, bool visible)
	:m_Visible(visible)
    , m_Spacig(spacing)
{
    ReadFileTop5();
    std::string player1 = "1 " + m_Leaderbord[0].first + " " + std::to_string(m_Leaderbord[0].second);
    std::string player2 = "2 " + m_Leaderbord[1].first + " " + std::to_string(m_Leaderbord[1].second);
    std::string player3 = "3 " + m_Leaderbord[2].first + " " + std::to_string(m_Leaderbord[2].second);
    std::string player4 = "4 " + m_Leaderbord[3].first + " " + std::to_string(m_Leaderbord[3].second);
    std::string player5 = "5 " + m_Leaderbord[4].first + " " + std::to_string(m_Leaderbord[4].second);
    m_pPlayer1 = std::make_shared<dae::TextObject>(player1, font);
    m_pPlayer2 = std::make_shared<dae::TextObject>(player2, font);
    m_pPlayer3 = std::make_shared<dae::TextObject>(player3, font);
    m_pPlayer4 = std::make_shared<dae::TextObject>(player4, font);
    m_pPlayer5 = std::make_shared<dae::TextObject>(player5, font);
}

void LeaderbordComp::Update(float elapsedSec)
{
    m_pPlayer1->Update(elapsedSec);
    m_pPlayer2->Update(elapsedSec);
    m_pPlayer3->Update(elapsedSec);
    m_pPlayer4->Update(elapsedSec);
    m_pPlayer5->Update(elapsedSec);
}

void LeaderbordComp::Render(glm::vec3 pos) const
{
    if (m_Visible) {
        m_pPlayer1->Render(pos);
        m_pPlayer2->Render(glm::vec3(pos.x, pos.y + m_Spacig, pos.z));
        m_pPlayer3->Render(glm::vec3(pos.x, pos.y + (m_Spacig * 2), pos.z));
        m_pPlayer4->Render(glm::vec3(pos.x, pos.y + (m_Spacig * 3), pos.z));
        m_pPlayer5->Render(glm::vec3(pos.x, pos.y + (m_Spacig * 4), pos.z));
    }
}

void LeaderbordComp::CheckPositionInLeaderbord(const std::string& name, int score)
{
    int position{ -1 };
    for (int i{4}; i >= 0; --i) {
        if (score > m_Leaderbord[i].second) {
            position = i;
        }
        else {
            break;
        }
    }
    if (position != -1) {
        if (position == 4) {
            m_Leaderbord[4].first = name;
            m_Leaderbord[4].second = score;
        }
        else {
            for (int i{ position + 1 }; i < 5; ++i) {
                m_Leaderbord[i].first = m_Leaderbord[i - 1].first;
                m_Leaderbord[i].second = m_Leaderbord[i - 1].second;
            }
            m_Leaderbord[position].first = name;
            m_Leaderbord[position].second = score;
        }
    }
}

void LeaderbordComp::Save()
{
    std::ofstream writeFile{ "../Data/Top5Gamers.txt",std::ios::binary };
    if (writeFile.is_open()) {
        for (int i{}; i < 5; ++i) {
            writeFile << m_Leaderbord.at(i).first << std::endl;
        }
        for (int i{}; i < 5; ++i) {
            writeFile << m_Leaderbord.at(i).second << std::endl;
        }
        writeFile.close();
    }
    else { std::cout << "Failed to open file!\n"; }
}

void LeaderbordComp::SetVisible(bool active)
{
    m_Visible = active;
}

void LeaderbordComp::ReadFileTop5()
{
	std::ifstream readFile{ "../Data/Top5Gamers.txt",std::ios::binary };
    if (readFile.is_open()) {
        std::string name{};
        int score{};
        for (int i{}; i < 5; ++i) {
            std::getline(readFile, name, static_cast<char>(0x0a));
            m_Leaderbord.push_back(std::pair<std::string, int>(name, 0));
        }
        for (int i{}; i < 5; ++i) {
            readFile >> score;
            m_Leaderbord.at(i).second = score;
        }
        readFile.close();
    }
    else {
        std::cout << "Failed to open file!\n";
    }
}
