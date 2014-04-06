#include "ListWidget.hpp"

std::string ListWidget::render(int w, int h) {
    //FIXME need to limit the output here!
//     return m_logfile.str();
    std::stringstream s;
    s << "|";
    int c = w-2;
    while(c--)
      s << " ";
    s << "|";
    for(int i=1; i < h; ++i) {
        s << i;
	if (i == h-1)
	  s << " - last line";
	else
	  s << std::endl;
    }
    return s.str();
}

void ListWidget::append(std::string line) {
    m_logfile << line;
}
