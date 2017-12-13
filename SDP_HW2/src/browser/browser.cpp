#include "browser.h"

Browser::Browser() : homepage("about:config") {
  browser.push_back(Tab(homepage));
  current = browser.begin();
}

Tab Browser::getCurrentTab() {
  return *current;
}

void Browser::go(std::string URL) {
  (*current).setURL(URL);
}

void Browser::insert(std::string URL) {
  browser.push_back(Tab(URL));
}

void Browser::back() {
  if(browser.getSize() > 1 && current != browser.begin()) {
    --current;
  }
}

void Browser::forward() {
  if(browser.getSize() > 1 && current != browser.last()) {
    ++current;
  }
}

void Browser::remove() {
  browser.removeAt(current);
}

void Browser::print() const {
  for(tit it = browser.begin(); it != browser.end(); ++it) {
    std::cout << (*it).getURL() << " " << (*it).getTimestamp() << std::endl;
  }
}

void Browser::sort(bool byURL) {
  if(byURL) {
    browser.sort<URLComparator>();
  } else {
    browser.sort<TimestampComparator>();
  }
}
