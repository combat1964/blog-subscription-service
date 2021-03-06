/**
 * @file
 * @author  Mohammad S. Babaei <info@babaei.net>
 * @version 0.1.0
 *
 * @section LICENSE
 *
 * (The MIT License)
 *
 * Copyright (c) 2016 Mohammad S. Babaei
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * The website home page.
 */


#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WString>
#include <Wt/WText>
#include <CoreLib/make_unique.hpp>
#include "CgiEnv.hpp"
#include "CgiRoot.hpp"
#include "ContactForm.hpp"
#include "Div.hpp"
#include "Home.hpp"
#include "Subscription.hpp"

using namespace std;
using namespace boost;
using namespace Wt;
using namespace Service;

struct Home::Impl : public Wt::WObject
{
public:
    Impl();
    ~Impl();
};

Home::Home()
    : Page(),
    m_pimpl(make_unique<Home::Impl>())
{
    WApplication *app = WApplication::instance();
    app->setTitle(tr("home-page-title").value());

    this->clear();
    this->setId("HomePage");
    this->setStyleClass("full-width full-height");
    this->addWidget(this->Layout());
}

Home::~Home() = default;

WWidget *Home::Layout()
{
    Div *container = new Div("Home", "full-width full-height");
    Div *noScript = new Div(container);
    noScript->addWidget(new WText(tr("no-script")));

    CgiRoot *cgiRoot = static_cast<CgiRoot *>(WApplication::instance());
    CgiEnv *cgiEnv = cgiRoot->GetCgiEnvInstance();

    if (cgiEnv->IsContactFormRequested()) {
        container->addWidget(new ContactForm());
        return container;
    }

    container->addWidget(new Subscription());

    return container;
}

Home::Impl::Impl()
{

}

Home::Impl::~Impl() = default;
