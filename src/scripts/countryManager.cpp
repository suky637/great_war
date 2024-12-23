#include "scripts/countryManager.h"
#include "gamelogic.h"

void CountryManager::Start()
{
}

void CountryManager::Update(GUI* gui)
{
    if (Game::instance.currentCountry != "" && !hasSelectedACountry) {
        std::cout << Game::instance.currentCountry << "\n";
        hasSelectedACountry = true;
        DynImageBox* ima = (DynImageBox*)gui->components["flags"]->GetComponent();
        if ("ressources/flags/" + Game::instance.currentCountry + ".png" != ima->path)
        {
            ima->Value("ressources/flags/" + Game::instance.currentCountry + ".png");
        }
        Button* button = (Button*)gui->components["Select_Country"]->GetComponent();
        button->forceEvent();
    }
    if (gui->Exist("flags") && !hasSelectedACountry)
    {
        DynImageBox* ima = (DynImageBox*)gui->components["flags"]->GetComponent();
        if ("ressources/flags/" + selectedCountry + ".png" != ima->path)
        {
            ima->Value("ressources/flags/" + selectedCountry + ".png");
        }
    }
    else if (gui->Exist("selectFlag") && hasSelectedACountry)
    {
        DynImageBox* ima = (DynImageBox*)gui->components["selectFlag"]->GetComponent();
        if ("ressources/flags/" + selectedCountry + ".png" != ima->path)
        {
            ima->Value("ressources/flags/" + selectedCountry + ".png");
        }
    }

    // Select GUI
    if (gui->Exist("Select_Country") && selectedCountry != "" && !hasSelectedACountry)
    {
        gui->components.at("Select_Country")->visible = true;
        if (gui->components.at("Select_Country")->isClicked)
        {
            hasSelectedACountry = true;
            Game::instance.currentCountry = selectedCountry;
            Game::instance.currentSave["country"] = Game::instance.currentCountry;
            if (gui->Exist("selectFlag"))
                gui->components.at("selectFlag")->visible = true;
            gui->components.at("Select_Country")->visible = false;
        }
    }
    else
    {
        gui->components.at("Select_Country")->visible = false;
    }
}

void CountryManager::FixedUpdate()
{

}

void CountryManager::Draw()
{
    
}