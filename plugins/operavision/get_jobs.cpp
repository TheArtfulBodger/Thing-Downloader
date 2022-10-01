#include <cpr/cpr.h>

#include <iostream>

#include <td/spec/v1.hpp>

#include <Document.h>
#include <Node.h>
#include <Selection.h>

#include "opera.hpp"

void get_jobs(const td::dl& base)
{
    // Get page with all performaces on
    auto rsp = cpr::Get(cpr::Url { "https://operavision.eu/performances" });
    CDocument doc;
    doc.parse(rsp.text);

    CSelection c = doc.find(".newsItem");

    for (int i = 0; i < c.nodeNum(); i++) {

        CNode title = c.nodeAt(i).childAt(0);
        CNode link = c.nodeAt(i).childAt(2);

        opera o;
        std::string name;
        o.name = name;
        name = title.find("h3").nodeAt(0).ownText();
        o.company = title.find(".titelSpan").nodeAt(0).text();

        std::string href = link.attribute("data-href");
        o.slug = href.substr(href.find_last_of('/') + 1);
        o.video_id = link.attribute("data-video-id");

        o.operation = download_mode_video;
        base->add_job(o.video_id + "_video", name + " (Video)", nlohmann::json(o).dump());

        o.operation = download_mode_desc;
        base->add_job(o.video_id + "_description", name + " (Description)", nlohmann::json(o).dump());
    }
}
