% -------------------------------------------------------------------
%  @LaTeX-class-file{
%     filename        = "papon_thesis.cls",
%     version         = "0.1",
%     date            = "6 January 2013",
%     codetable       = "ISO/ASCII",
%     keywords        = "LaTeX, papon_thesis",
%     supported       = "send email to jpapon@gmail.com",
%     docstring       = "A thesis class for PhD dissertations."
% --------------------------------------------------------------------

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{papon_thesis}[2014/05/06 v0.2 Jeremie Papon Thesis Class - based off Harvard Thesis Class]
\LoadClass[12pt, twoside, a4paper]{book}

% Required packages
\RequirePackage{watermark}
\RequirePackage{graphicx}
\RequirePackage[bookmarks, 
                colorlinks=true, 
                citecolor=Crimson,
                filecolor=black,
                linkcolor=DarkBlue,
                urlcolor=Crimson,
                pdfdisplaydoctitle=true,
                pdftitle={Perceptual Segmentation of Visual Streams by Tracking of Objects and Parts}, pdfauthor={J\'{e}r\'{e}mie Papon}, pdfsubject={Dissertation},
                pdfkeywords={Visual Tracking, Object Segmentation, Video Segmentation, Pointclouds}
                ]{hyperref} 



\RequirePackage[acronym,nonumberlist]{glossaries}
\RequirePackage[centertags]{amsmath}
\RequirePackage{amssymb}
\RequirePackage[numbers, comma, sort&compress]{natbib}
\RequirePackage[small, md, sc]{titlesec}
\RequirePackage[tight,nice]{units}
\RequirePackage{verbatim}
\RequirePackage[toc,page]{appendix}
\RequirePackage[caption=false]{subfig}
\RequirePackage{epigraph}

% colors
\RequirePackage{xcolor}
\definecolor{Crimson}{rgb}{0.6471, 0.1098, 0.1882}
\definecolor{DarkBlue}{rgb}{0.1216, 0.1843, 0.2902}
\definecolor{Silver}{rgb}{0.5490, 0.5451, 0.5882}


\RequirePackage{url}
\RequirePackage[titles,subfigure]{tocloft}
\setcounter{tocdepth}{3}
\usepackage{etoolbox}
\preto\section{%
  \ifnum\value{section}=0\addtocontents{toc}{\vskip10pt}\fi
}
%\preto\figure{%
%  \ifnum\value{figure}=0\addtocontents{lof}{{\bfseries Chapter \thechapter\vskip10pt}}\fi
%}

\renewcommand{\cftchapfont}{\normalsize \scshape}



\RequirePackage{pdfsync} %do pdf synchronization [andy]

%\usepackage[closeFloats, noSeparatorLine]{fltpage} %use the custom modified fltpage package
\RequirePackage{afterpage}








\synctex=1 % turn synctex on automatically to sync between pdf viewer [andy]

%   list an entire bibliography entry inline. Useful for acknowledging when my paper was previously published
\RequirePackage{bibentry}
\nobibliography*

\RequirePackage{lettrine} % big letter at start of chapter
\RequirePackage[inner=40mm, outer=25mm, top=25mm, bottom=25mm, a4paper]{geometry}

\RequirePackage{fancyhdr}
\pagestyle{fancy} % options: empty , plain , fancy
\RequirePackage[palatino]{quotchap}
\definecolor{chaptergrey}{rgb}{0.5490, 0.5451, 0.5882}
\RequirePackage{titling}
\RequirePackage{setspace}
\RequirePackage{booktabs} % for much better looking tables
\RequirePackage[labelfont={rm,bf,small},textfont={rm,small},justification=RaggedRight,margin=0pt, figurewithin=section, tablewithin=section]{caption}
\RequirePackage{packages/foreign}
\RequirePackage{multirow}

\doublespacing
\addtolength{\footnotesep}{\footnotesep}

%\raggedright

\parindent 12pt
\RequirePackage{mathspec}

% use Arno Pro instead of standard LaTeX fonts
\setmathsfont(Digits,Latin,Greek)[Numbers={Lining,Proportional}]{Arno Pro}

\setmathrm{Arno Pro}

\RequirePackage{fontspec,xltxtra,xunicode}
\defaultfontfeatures{Mapping=tex-text, Numbers=OldStyle}
\aliasfontfeatureoption{Ligatures}{Historic}{Historical}
\setromanfont[Mapping=tex-text,
              Numbers=OldStyle,
              Ligatures={Common}]{Arno Pro} %

%Set fonts for Mac Specific (Comment out on Windows XP)
%\setsansfont[Scale=MatchLowercase,Mapping=tex-text]{Helvetica Neue}
%\setmonofont[Scale=MatchLowercase]{Consolas}

% some definitions
\def\degreeyear#1{\gdef\@degreeyear{#1}}
\def\degreemonth#1{\gdef\@degreemonth{#1}}
\def\degree#1{\gdef\@degree{#1}}
\def\advisor#1{\gdef\@advisor{#1}}
\def\department#1{\gdef\@department{#1}}
\def\field#1{\gdef\@field{#1}}
\def\university#1{\gdef\@university{#1}}
\def\universitycity#1{\gdef\@universitycity{#1}}
\def\universitystate#1{\gdef\@universitystate{#1}}


\renewcommand{\maketitle}{
  \singlespacing
  \thispagestyle{empty}
  \begin{flushright}
  \vspace*{100pt} 
  \Huge \textcolor{DarkBlue}{\textit{\thetitle}} \vspace{10pt}
  \textcolor{Silver}{\rule{\textwidth}{2.0pt}}
  \normalsize \sc Dissertation \\ 
  \vspace{6pt}
  in order to obtain the doctoral degree in Mathematics and Natural Sciences\\ 
  "Doctor rerum naturalium" \\
  \vspace{6pt}
  of the Georg-August-Universit\"{a}t G\"{o}ttingen \\
  \vspace{6pt}
  in the Doctoral program of \\
  the Georg-August University School of Science (GAUSS) \\
  \vspace{24pt}
  submitted by\\
  \theauthor
  \vspace{12pt} 
  of Summit, NJ, USA \\
  \vspace{100pt}
  \includegraphics[width=30mm]{figures/UniLogo1} \\
  \vspace{12pt} 
  \@university\\ \@universitycity, \@universitystate\\
  \@degreemonth\ \@degreeyear \\
  \vspace*{\fill}
  \end{flushright}
}

\newcommand{\makegermantitle}{
  \singlespacing
  \thispagestyle{empty}
  \begin{flushright}
  \vspace*{100pt} 
  \Huge \textcolor{DarkBlue}{\textit{\thetitle}} \vspace{10pt}
  \textcolor{Silver}{\rule{\textwidth}{2.0pt}}
  \normalsize \sc Dissertation \\ 
  \vspace{6pt}
  zur Erlangung des mathematisch-naturwissenschaftlichen Doktorgrades \\ 
  "Doctor rerum naturalium" \\
  \vspace{6pt}
  der Georg-August-Universit\"{a}t G\"{o}ttingen \\
  \vspace{6pt}
  im Promotionsprogramm \\
  der Georg-August University School of Science (GAUSS) \\
  \vspace{24pt}
  vorgelegt von\\
  \theauthor
  \vspace{12pt} 
  aus Summit, NJ, USA \\
  \vspace{100pt}
  \includegraphics[width=30mm]{figures/UniLogo1} \\
  \vspace{12pt}
  G\"{o}ttingen, 2014 \\
  \vspace*{\fill}
  \end{flushright}
}

\newcommand{\referentpage}{
  \thispagestyle{empty}
  \begin{flushleft}
  \vspace*{150mm}
  Referentin/Referent: Prof. Dr. Florentin W\"org\"otter \\
  Koreferentin/Koreferent: Prof. Dr. Dieter Hogrefe \\
  Tag der m\"undlichen Pr\"ufung: 
  \end{flushleft}
}

\newcommand{\abstractpage}{
  \newpage
  \pagenumbering{roman}
  \setcounter{page}{3}
  \pagestyle{fancy}
  \renewcommand{\headrulewidth}{0.0pt}
  \begin{center}
  \vspace*{1pt}
  \huge \textcolor{DarkBlue}{\textit{\@title}} \\
  \vspace*{15pt}
  \Large \sc Abstract \\ \rm
  \end{center}
  \doublespace %Harvard registrar requests that abstract is double spaced
  \input{frontmatter/abstract}
  \doublespace %Harvard registrar requests that abstract is double spaced
  \newpage \lhead{} \rhead{}
  \cfoot{\thepage}
  \onehalfspacing
}

\newcommand{\dedicationpage}{
  \pagestyle{fancy}
  \newpage \thispagestyle{fancy} \vspace*{\fill}
  \sc \noindent \input{frontmatter/dedication}
  \vspace*{\fill} \newpage \rm
  }

% the list of authors
\newcommand{\authorlist}{
  \pagestyle{fancy}
  \newpage
  \thispagestyle{fancy}
  \chapter*{Author List}
  \noindent \input{frontmatter/authorlist}
  \newpage \rm
  }

% the acknowledgments page
\newcommand{\acknowledgments}{
  \input{frontmatter/thanks}
  \vspace*{\fill}
  \newpage
  \setcounter{page}{1}
  \pagenumbering{arabic}}

% An environment for paragraph-style section
\providecommand\newthought[1]{%
   \addvspace{1.0\baselineskip plus 0.5ex minus 0.2ex}%
   \noindent\textsc{#1}}

   
%This adds chapter names to list of figures
\usepackage{etoolbox}
\makeatletter
\newcommand{\thechaptername}{}
\newcounter{chapter@last}
\renewcommand{\chaptermark}[1]
             {%
               \markboth{#1}{}%
               \renewcommand{\thechaptername}{#1}%
             }
\pretocmd{\caption}
         {%
           \ifnumequal%
               {\value{chapter}}%
               {\value{chapter@last}}%
               {}%  already added
               {%
                 \addtocontents{lof}%
                               {\protect\numberline{\bfseries\thechapter\quad\thechaptername}}%
                 \setcounter{chapter@last}{\value{chapter}}%
               }%
         }
         {}
         {}%  failed, could put some error message here...
\makeatother