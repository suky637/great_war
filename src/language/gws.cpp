#include "language/gws.h"
#include "engine/colour.h"
#include "gamelogic.h"
#include "myguilib.h"

std::vector<std::string> GWS::split(std::string& str, std::string delimiters, std::string usefulDel)
{
    std::vector<std::string> tokens;
    if (delimiters.empty() && usefulDel.empty()) {
        tokens.push_back("W" + str);
        return tokens;
    }

    std::string allDelimiters = delimiters + usefulDel;
    size_t start = 0;
    size_t end = str.find_first_of(allDelimiters);

    while (end != std::string::npos) {
        if (end > start)
            tokens.push_back("W" + str.substr(start, end - start));
        if (usefulDel.find(str.at(end)) != std::string::npos)
        {
            tokens.push_back("D" + std::string(1, str.at(end)));
        }
        start = end + 1;
        end = str.find_first_of(allDelimiters, start);
    }

    if (start < str.size())
        tokens.push_back("W" + str.substr(start));
    
    return tokens;
}

void GWS::interpret(std::string file) {
    std::ifstream f{file, std::ios::in};
    if (!f) {
        std::cerr << TEXT_RED "Error, file not found / unable to open, skipping this file\n" RESET_COLOR;
        return;
    }

    std::string line;
    while (std::getline(f, line)) {
        // tokenizer here
        std::vector<std::string> tokens = this->split(line, " \t", "\"[]:,");
        tokens.push_back("D\n");
        this->tokens.insert(this->tokens.end(), tokens.begin(), tokens.end());
    }

    // Finding each headers
    for (int i = 0; i < tokens.size(); i++) {
        //std::cout << TEXT_RED << tokens.at(i) << "\n" RESET_COLOR;
        if (tokens.at(i) == "D:") {
            // Found a function

            // Finding the type of event
            std::string type = tokens.at(i-2).substr(1);
            std::string id = tokens.at(i-4).substr(1);
            GWS_Event ev;
            ev.start = i+1;
            int j = i+1;
            while (tokens.at(j) != "D:" && j < tokens.size() - 1) {
                j++;
            }
            if (tokens.at(j) == "D:")
                ev.end = j - 5;
            if (j == tokens.size() - 1)
                ev.end = j;
            //std::cout << ev.start << ", " << ev.end << "\n";
            
            if (type == "onClick") {
                ev.type = GWS_EventTypes::ON_CLICKED;
            }
            ev.id = id;
            events.push_back(ev);
        }
    }

    f.close();
    return;
}

int GWS::getEvent(std::string id, GWS_EventTypes type) {
    int ind = 0;
    for (auto e : events) {
        if (e.id == id && e.type == type)
            return ind;
        ind++;
    }
    return -1;
}

void GWS::runEvent(std::string id, GWS_EventTypes e, GUI* gui) {
    int _ind = this->getEvent(id, e);
    for (int i = events.at(_ind).start; i < events.at(_ind).end; i++) {
        if (tokens.at(i) == "Wset") {
            if (tokens.at(i+1) == "Wscene") {
                Game::instance.ChangeScene(std::stoi(tokens.at(i+2).substr(1)));
                i += 2;
            }
            if (tokens.at(i+2) == "Whide") {
                //std::cout << "'" << tokens.at(i+1).substr(1) << "'\n";
                gui->components.at(tokens.at(i+1).substr(1))->visible = false;
                
            }
            if (tokens.at(i+2) == "Wshow") {
                gui->components[tokens.at(i+1).substr(1)]->visible = true;
            }
        }
        else if (tokens.at(i) == "Wcall") {
            if (tokens.at(i+1) == "Wexit") {
                exit(0);
            }
        }
    }
}
