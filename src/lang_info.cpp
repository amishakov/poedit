/*
 *  This file is part of Poedit (http://www.poedit.net)
 *
 *  Copyright (C) 2013 Vaclav Slavik
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 *
 */

#include "lang_info.h"

#include <mutex>
#include <unordered_map>

static std::mutex gs_mutexGetPluralFormForLanguage;

std::string GetPluralFormForLanguage(std::string lang)
{
    if ( lang.empty() )
        return std::string();

    std::lock_guard<std::mutex> lock(gs_mutexGetPluralFormForLanguage);

    static const std::unordered_map<std::string, std::string> forms = {
        // Code generated with scripts/extract-plural-forms.py begins here

        { "af"   , "nplurals=2; plural=(n != 1);" },
        { "ak"   , "nplurals=2; plural=(n > 1);" },
        { "aln"  , "nplurals=2; plural=(n != 1);" },
        { "am"   , "nplurals=2; plural=(n > 1);" },
        { "am_ET", "nplurals=2; plural=(n != 1);" },
        { "an"   , "nplurals=2; plural=(n != 1);" },
        { "ar"   , "nplurals=6; plural=(n==0 ? 0 : n==1 ? 1 : n==2 ? 2 : n%100>=3 && n%100<=10 ? 3 : n%100>=11 && n%100<=99 ? 4 : 5);" },
        { "ar_SA", "nplurals=2; plural=(n != 1);" },
        { "arn"  , "nplurals=2; plural=(n > 1);" },
        { "as"   , "nplurals=2; plural=(n != 1);" },
        { "ast"  , "nplurals=2; plural=(n != 1);" },
        { "az"   , "nplurals=2; plural=(n != 1);" },
        { "bal"  , "nplurals=2; plural=(n != 1);" },
        // There are 4 forms according to
        // http://www.unicode.org/cldr/charts/supplemental/language_plural_rules.html#be
        // but the 4th one is not used for natural numbers
        { "be"   , "nplurals=3; plural=(n%10==1 && n%100!=11 ? 0 : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2);" },
        { "bg"   , "nplurals=2; plural=(n != 1);" },
        { "bn"   , "nplurals=2; plural=(n != 1);" },
        { "bo"   , "nplurals=1; plural=0;" },
        { "br"   , "nplurals=2; plural=(n > 1);" },
        { "brx"  , "nplurals=2; plural=(n != 1);" },
        { "bs"   , "nplurals=3; plural=(n%10==1 && n%100!=11 ? 0 : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2);" },
        { "ca"   , "nplurals=2; plural=(n != 1);" },
        { "crh"  , "nplurals=1; plural=0;" },
        { "cs"   , "nplurals=3; plural=(n==1) ? 0 : (n>=2 && n<=4) ? 1 : 2;" },
        { "csb"  , "nplurals=3; plural=(n==1 ? 0 : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2;" },
        { "cy"   , "nplurals=4; plural=(n==1) ? 0 : (n==2) ? 1 : (n != 8 && n != 11) ? 2 : 3;" },
        { "da"   , "nplurals=2; plural=(n != 1);" },
        { "de"   , "nplurals=2; plural=(n != 1);" },
        { "dz"   , "nplurals=1; plural=0;" },
        { "el"   , "nplurals=2; plural=(n != 1);" },
        { "en"   , "nplurals=2; plural=(n != 1);" },
        { "eo"   , "nplurals=2; plural=(n != 1);" },
        { "es"   , "nplurals=2; plural=(n != 1);" },
        { "et"   , "nplurals=2; plural=(n != 1);" },
        { "eu"   , "nplurals=2; plural=(n != 1);" },
        { "fa"   , "nplurals=1; plural=0;" },
        { "fi"   , "nplurals=2; plural=(n != 1);" },
        { "fil"  , "nplurals=2; plural=(n > 1);" },
        { "fo"   , "nplurals=2; plural=(n != 1);" },
        { "fr"   , "nplurals=2; plural=(n > 1);" },
        { "frp"  , "nplurals=2; plural=(n > 1);" },
        { "fur"  , "nplurals=2; plural=(n != 1);" },
        { "fy"   , "nplurals=2; plural=(n != 1);" },
        { "ga"   , "nplurals=5; plural=(n==1 ? 0 : n==2 ? 1 : n<7 ? 2 : n<11 ? 3 : 4);" },
        { "gd"   , "nplurals=3; plural=(n < 2 ? 0 : n == 2 ? 1 : 2);" },
        { "gl"   , "nplurals=2; plural=(n != 1);" },
        { "gu"   , "nplurals=2; plural=(n != 1);" },
        { "gun"  , "nplurals=2; plural=(n > 1);" },
        { "ha"   , "nplurals=2; plural=(n != 1);" },
        { "he"   , "nplurals=2; plural=(n != 1);" },
        { "hi"   , "nplurals=2; plural=(n != 1);" },
        { "hne"  , "nplurals=2; plural=(n != 1);" },
        { "hr"   , "nplurals=3; plural=(n%10==1 && n%100!=11 ? 0 : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2);" },
        { "hsb"  , "nplurals=4; plural=(n%100==1 ? 0 : n%100==2 ? 1 : n%100==3 || n%100==4 ? 2 : 3);" },
        { "ht"   , "nplurals=2; plural=(n != 1);" },
        { "hu"   , "nplurals=2; plural=(n != 1);" },
        { "hy"   , "nplurals=2; plural=(n != 1);" },
        { "ia"   , "nplurals=2; plural=(n != 1);" },
        { "id"   , "nplurals=1; plural=0;" },
        { "ig"   , "nplurals=2; plural=(n != 1);" },
        { "ilo"  , "nplurals=2; plural=(n != 1);" },
        { "is"   , "nplurals=2; plural=(n != 1);" },
        { "it"   , "nplurals=2; plural=(n != 1);" },
        { "ja"   , "nplurals=1; plural=0;" },
        { "jv"   , "nplurals=2; plural=(n != 1);" },
        { "ka"   , "nplurals=1; plural=0;" },
        { "kk"   , "nplurals=1; plural=0;" },
        { "km"   , "nplurals=1; plural=0;" },
        { "kn"   , "nplurals=1; plural=0;" },
        { "ko"   , "nplurals=1; plural=0;" },
        { "ks"   , "nplurals=2; plural=(n != 1);" },
        { "ku"   , "nplurals=2; plural=(n != 1);" },
        { "kw"   , "nplurals=4; plural=(n==1) ? 0 : (n==2) ? 1 : (n == 3) ? 2 : 3;" },
        { "ky"   , "nplurals=1; plural=0;" },
        { "la"   , "nplurals=2; plural=(n != 1);" },
        { "lb"   , "nplurals=2; plural=(n != 1);" },
        { "li"   , "nplurals=2; plural=(n != 1);" },
        { "ln"   , "nplurals=2; plural=(n > 1);" },
        { "lo"   , "nplurals=1; plural=0;" },
        { "lt"   , "nplurals=3; plural=(n%10==1 && n%100!=11 ? 0 : n%10>=2 && (n%100<10 || n%100>=20) ? 1 : 2);" },
        { "lv"   , "nplurals=3; plural=(n%10==1 && n%100!=11 ? 0 : n != 0 ? 1 : 2);" },
        { "mai"  , "nplurals=2; plural=(n != 1);" },
        { "mg"   , "nplurals=2; plural=(n > 1);" },
        { "mi"   , "nplurals=2; plural=(n > 1);" },
        { "mk"   , "nplurals=2; plural=(n % 10 == 1 && n % 100 != 11) ? 0 : 1;" },
        { "ml"   , "nplurals=2; plural=(n != 1);" },
        { "mn"   , "nplurals=2; plural=(n != 1);" },
        { "mr"   , "nplurals=2; plural=(n != 1);" },
        { "ms"   , "nplurals=1; plural=0;" },
        { "mt"   , "nplurals=4; plural=(n==1 ? 0 : n==0 || ( n%100>1 && n%100<11) ? 1 : (n%100>10 && n%100<20 ) ? 2 : 3);" },
        { "my"   , "nplurals=1; plural=0;" },
        { "nah"  , "nplurals=2; plural=(n != 1);" },
        { "nap"  , "nplurals=2; plural=(n != 1);" },
        { "nb"   , "nplurals=2; plural=(n != 1);" },
        { "nds"  , "nplurals=2; plural=(n != 1);" },
        { "ne"   , "nplurals=2; plural=(n != 1);" },
        { "nl"   , "nplurals=2; plural=(n != 1);" },
        { "nn"   , "nplurals=2; plural=(n != 1);" },
        { "no"   , "nplurals=2; plural=(n != 1);" },
        { "nr"   , "nplurals=1; plural=0;" },
        { "nso"  , "nplurals=2; plural=(n > 1);" },
        { "oc"   , "nplurals=2; plural=(n > 1);" },
        { "or"   , "nplurals=2; plural=(n != 1);" },
        { "pa"   , "nplurals=2; plural=(n != 1);" },
        { "pap"  , "nplurals=2; plural=(n != 1);" },
        { "pl"   , "nplurals=3; plural=(n==1 ? 0 : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2);" },
        { "pms"  , "nplurals=2; plural=(n != 1);" },
        { "ps"   , "nplurals=2; plural=(n != 1);" },
        { "pt"   , "nplurals=2; plural=(n != 1);" },
        { "pt_BR", "nplurals=2; plural=(n > 1);" },
        { "rm"   , "nplurals=2; plural=(n != 1);" },
        { "ro"   , "nplurals=3; plural=(n==1?0:(((n%100>19)||((n%100==0)&&(n!=0)))?2:1));" },
        { "ru"   , "nplurals=3; plural=(n%10==1 && n%100!=11 ? 0 : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2);" },
        { "rw"   , "nplurals=2; plural=(n != 1);" },
        { "sc"   , "nplurals=2; plural=(n != 1);" },
        { "sco"  , "nplurals=2; plural=(n != 1);" },
        { "se"   , "nplurals=2; plural=(n != 1);" },
        { "si"   , "nplurals=2; plural=(n != 1);" },
        { "sk"   , "nplurals=3; plural=(n==1) ? 0 : (n>=2 && n<=4) ? 1 : 2;" },
        { "sl"   , "nplurals=4; plural=(n%100==1 ? 0 : n%100==2 ? 1 : n%100==3 || n%100==4 ? 2 : 3);" },
        { "sm"   , "nplurals=1; plural=0;" },
        { "sn"   , "nplurals=2; plural=(n != 1);" },
        { "so"   , "nplurals=2; plural=(n != 1);" },
        { "son"  , "nplurals=1; plural=0;" },
        { "sq"   , "nplurals=2; plural=(n != 1);" },
        { "sr"   , "nplurals=3; plural=(n%10==1 && n%100!=11 ? 0 : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2);" },
        { "st"   , "nplurals=2; plural=(n != 1);" },
        { "su"   , "nplurals=1; plural=0;" },
        { "sv"   , "nplurals=2; plural=(n != 1);" },
        { "sw"   , "nplurals=2; plural=(n != 1);" },
        { "ta"   , "nplurals=2; plural=(n != 1);" },
        { "te"   , "nplurals=2; plural=(n != 1);" },
        { "tg"   , "nplurals=2; plural=(n != 1);" },
        { "th"   , "nplurals=1; plural=0;" },
        { "ti"   , "nplurals=2; plural=(n > 1);" },
        { "tk"   , "nplurals=2; plural=(n != 1);" },
        { "tl"   , "nplurals=2; plural=(n > 1);" },
        { "tlh"  , "nplurals=2; plural=(n > 1);" },
        { "to"   , "nplurals=1; plural=0;" },
        { "tr"   , "nplurals=1; plural=0;" },
        { "tt"   , "nplurals=1; plural=0;" },
        { "udm"  , "nplurals=1; plural=0;" },
        { "ug"   , "nplurals=1; plural=0;" },
        { "uk"   , "nplurals=3; plural=(n%10==1 && n%100!=11 ? 0 : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2);" },
        { "ur"   , "nplurals=2; plural=(n != 1);" },
        { "uz"   , "nplurals=1; plural=0;" },
        { "ve"   , "nplurals=2; plural=(n != 1);" },
        { "vi"   , "nplurals=1; plural=0;" },
        { "vls"  , "nplurals=2; plural=(n != 1);" },
        { "wa"   , "nplurals=2; plural=(n > 1);" },
        { "wo"   , "nplurals=1; plural=0;" },
        { "xh"   , "nplurals=2; plural=(n != 1);" },
        { "yi"   , "nplurals=2; plural=(n != 1);" },
        { "yo"   , "nplurals=2; plural=(n != 1);" },
        { "zh"   , "nplurals=1; plural=0;" },
        { "zu"   , "nplurals=2; plural=(n != 1);" }

        // Code generated with scripts/extract-plural-forms.py ends here
    };

    auto i = forms.find(lang);
    if ( i != forms.end() )
        return i->second;

    size_t pos = lang.rfind('@');
    if ( pos != std::string::npos )
    {
        lang = lang.substr(0, pos);
        i = forms.find(lang);
        if ( i != forms.end() )
            return i->second;
    }

    pos = lang.rfind('_');
    if ( pos != std::string::npos )
    {
        lang = lang.substr(0, pos);
        i = forms.find(lang);
        if ( i != forms.end() )
            return i->second;
    }

    return std::string();
}
