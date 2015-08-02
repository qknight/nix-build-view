#include "BuildWidgetManager.hpp"
#include "BuildWidget.hpp"
#include "TerminalWidget.hpp"
#include "StatusWidget.hpp"

#include <algorithm>

BuildWidgetManager::BuildWidgetManager()
{
}

int
BuildWidgetManager::type() const
{
    return WidgetName::BuildWidgetManager;
}

BuildWidgetManager*
BuildWidgetManager::Instance()
{
    static BuildWidgetManager* _instance = new BuildWidgetManager;
    return _instance;
}

bool
BuildWidgetManagerSort(const Widget* a, const  Widget* b)
{
    if ((a->type() == WidgetName::BuildWidget) &&
            (b->type() == WidgetName::BuildWidget))
    {
        const BuildWidget* f1 = dynamic_cast<const BuildWidget*>(a);
        const BuildWidget* f2 = dynamic_cast<const BuildWidget*>(b);

        return f1->getPhase() > f2->getPhase();
    }

    return false;
}

void
BuildWidgetManager::sort()
{
    std::stable_sort(m_widgets.begin(),
                     m_widgets.end(),
                     BuildWidgetManagerSort);
}

// it is assumed that the given UUID is already uniq
void
BuildWidgetManager::addBuild(std::string UUID,
                             std::vector<std::string> phases)
{
    add(new BuildWidget(UUID, phases));
    StatusWidget::Instance()->setBuilds(m_widgets.size());
}

void
BuildWidgetManager::removeBuild(std::string UUID)
{
//FIXME todo
    StatusWidget::Instance()->setBuilds(m_widgets.size());
}

int
BuildWidgetManager::getPhase(std::string UUID)
{
    //FIXME refactor this function into a general resolver function
    for(unsigned int i = 0; i < m_widgets.size(); ++i) {
        BuildWidget* v = dynamic_cast<BuildWidget*>(m_widgets[i]);

        if (v->m_name == UUID) {
            return v->m_currentPhase;
        }
    }

    return -1;
}

void
BuildWidgetManager::setPhase(std::string UUID, int phase)
{
    for(unsigned int i = 0; i < m_widgets.size(); ++i)
    {
        BuildWidget* v = dynamic_cast<BuildWidget*>(m_widgets[i]);

        if (v->m_name == UUID) {
            v->m_currentPhase = phase;

            if (v->m_currentPhase ==  v->m_phases.size()) {
                AdvancedStringContainer v;
                v << "Build of "
                  << AdvancedString(UUID, COLOR_MAGENTA)
                  << " completed\n";

                TerminalWidget::Instance()->append(v);
                sort();
                m_widgets.erase(m_widgets.begin());
                update();

                // FIXME when removing elements, move the view upwards since it
                // runs out of items currently
                StatusWidget::Instance()->setBuilds(m_widgets.size());

                // FIXME use interl remove fkt
            }

            return;
        }
    }
}

