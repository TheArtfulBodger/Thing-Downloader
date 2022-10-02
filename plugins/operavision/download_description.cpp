#include <cpr/cpr.h>

#include <filesystem>
#include <fstream>
#include <iostream>

#include <td/spec/v1.hpp>

#include <Document.h>
#include <Node.h>
#include <Selection.h>

#include <tinyxml2.h>

#include "opera.hpp"

void download_description(const td::dl& base, const td::job& job)
{
    auto o = nlohmann::json::parse(job->get_job_data()).get<opera>();

    // Get page for performance on
    auto uri = "https://operavision.eu/performance/" + o.slug;
    auto rsp = cpr::Get(cpr::Url { uri });
    CDocument doc;
    doc.parse(rsp.text);

    tinyxml2::XMLDocument xdoc = tinyxml2::XMLDocument();
    auto* decl = xdoc.NewDeclaration(nullptr);
    xdoc.LinkEndChild(decl);

    auto* video = xdoc.NewElement("video");
    xdoc.LinkEndChild(video);

    // UniqueID
    {
        auto* elem = xdoc.NewElement("uniqueid");
        video->LinkEndChild(elem);

        elem->SetAttribute("type", "ovdl");
        elem->SetText(uri.c_str());
    }

    // Title
    {
        auto* elem = xdoc.NewElement("title");
        video->LinkEndChild(elem);
        elem->SetText(o.name.c_str());
    }

    // Outline
    {
        auto* elem = xdoc.NewElement("outline");
        video->LinkEndChild(elem);

        auto outline = doc.find("p.intro")
                           .nodeAt(0)
                           .text();

        elem->SetText(outline.c_str());
    }

    // Plot
    {
        auto* elem = xdoc.NewElement("plot");
        video->LinkEndChild(elem);

        auto nodes = doc.find("p.intro")
                         .nodeAt(0)
                         .parent()
                         .find("p:not(.intro)");

        std::string plot;
        for (int i = 0; i < nodes.nodeNum(); i++) {
            plot += nodes.nodeAt(i).text() + "\n\n";
        }

        elem->SetText(plot.c_str());
    }

    // Cast
    {
        auto nodes = doc.find(".castTable .castRow");
        for (int i = 0; i < nodes.nodeNum(); i++) {
            auto* elem = xdoc.NewElement("actor");
            video->LinkEndChild(elem);

            auto* elem2 = xdoc.NewElement("name");
            elem->LinkEndChild(elem2);

            auto* elem3 = xdoc.NewElement("role");
            elem->LinkEndChild(elem3);

            auto th = nodes.nodeAt(i).childAt(0).text();
            elem3->SetText(th.c_str());

            auto td = nodes.nodeAt(i).childAt(1).text();
            elem2->SetText(td.c_str());
        }
    }

    // Time
    {
        auto* elem = xdoc.NewElement("date");
        video->LinkEndChild(elem);

        auto date = doc.find(".performancedate time")
                        .nodeAt(0)
                        .attribute("datetime");

        elem->SetText(date.c_str());
    }

    // Write To Disk
    auto folder = std::filesystem::path(base->get_outpath_folder()) / o.company / o.name;
    auto outfile = folder / (o.slug + ".nfo");
    std::filesystem::create_directories(folder);

    xdoc.SaveFile(outfile.string().c_str());

    job->set_complete(job->get_job_data(), false);
}