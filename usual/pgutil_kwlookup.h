/* ANSI-C code produced by gperf version 3.0.1 */
/* Command-line: gperf -m5 usual/pgutil_kwlookup.gp  */
/* Computed positions: -k'1-3,6,9,$' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 13 "usual/pgutil_kwlookup.gp"
struct PgKeyword { short name; short type; };
/* maximum key range = 1770, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
pg_keyword_lookup_hash (register const char *str, register unsigned int len)
{
  static const unsigned short asso_values[] =
    {
      1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788,
      1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788,
      1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788,
      1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788,
      1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788,
      1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788,
      1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788,
      1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788,
      1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788,
      1788, 1788, 1788, 1788, 1788,    2, 1788,   26,  553,   39,
       147,    2,  419,  330,  395,  231,    2,   31,  108,  328,
         2,   71,  304,    3,   14,    5,    4,  221,  454,  516,
       568,  447,    3, 1788, 1788, 1788, 1788, 1788, 1788, 1788,
      1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788,
      1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788,
      1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788,
      1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788,
      1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788,
      1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788,
      1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788,
      1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788,
      1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788,
      1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788,
      1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788,
      1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788, 1788,
      1788, 1788, 1788, 1788, 1788, 1788
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[8]];
      /*FALLTHROUGH*/
      case 8:
      case 7:
      case 6:
        hval += asso_values[(unsigned char)str[5]];
      /*FALLTHROUGH*/
      case 5:
      case 4:
      case 3:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
        hval += asso_values[(unsigned char)str[1]];
      /*FALLTHROUGH*/
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval + asso_values[(unsigned char)str[len - 1]];
}

struct pgkw_t
  {
    char pgkw_str18[sizeof("set")];
    char pgkw_str22[sizeof("sequence")];
    char pgkw_str28[sizeof("rename")];
    char pgkw_str29[sizeof("treat")];
    char pgkw_str30[sizeof("reset")];
    char pgkw_str34[sizeof("returns")];
    char pgkw_str36[sizeof("at")];
    char pgkw_str37[sizeof("strict")];
    char pgkw_str38[sizeof("as")];
    char pgkw_str40[sizeof("enable")];
    char pgkw_str44[sizeof("start")];
    char pgkw_str45[sizeof("stable")];
    char pgkw_str46[sizeof("restart")];
    char pgkw_str49[sizeof("range")];
    char pgkw_str53[sizeof("assertion")];
    char pgkw_str54[sizeof("assignment")];
    char pgkw_str55[sizeof("server")];
    char pgkw_str56[sizeof("escape")];
    char pgkw_str65[sizeof("create")];
    char pgkw_str66[sizeof("analyze")];
    char pgkw_str68[sizeof("analyse")];
    char pgkw_str73[sizeof("recursive")];
    char pgkw_str75[sizeof("standalone")];
    char pgkw_str76[sizeof("case")];
    char pgkw_str77[sizeof("on")];
    char pgkw_str78[sizeof("cast")];
    char pgkw_str79[sizeof("action")];
    char pgkw_str81[sizeof("none")];
    char pgkw_str82[sizeof("zone")];
    char pgkw_str83[sizeof("createuser")];
    char pgkw_str84[sizeof("not")];
    char pgkw_str92[sizeof("session")];
    char pgkw_str94[sizeof("statistics")];
    char pgkw_str101[sizeof("or")];
    char pgkw_str110[sizeof("nosuperuser")];
    char pgkw_str111[sizeof("cache")];
    char pgkw_str112[sizeof("asc")];
    char pgkw_str120[sizeof("access")];
    char pgkw_str121[sizeof("else")];
    char pgkw_str123[sizeof("cost")];
    char pgkw_str124[sizeof("continue")];
    char pgkw_str125[sizeof("content")];
    char pgkw_str129[sizeof("select")];
    char pgkw_str132[sizeof("recheck")];
    char pgkw_str134[sizeof("cross")];
    char pgkw_str138[sizeof("release")];
    char pgkw_str142[sizeof("constraint")];
    char pgkw_str144[sizeof("constraints")];
    char pgkw_str145[sizeof("least")];
    char pgkw_str146[sizeof("no")];
    char pgkw_str147[sizeof("last")];
    char pgkw_str148[sizeof("to")];
    char pgkw_str150[sizeof("national")];
    char pgkw_str151[sizeof("coalesce")];
    char pgkw_str154[sizeof("real")];
    char pgkw_str155[sizeof("large")];
    char pgkw_str157[sizeof("alter")];
    char pgkw_str163[sizeof("stdin")];
    char pgkw_str166[sizeof("nocreaterole")];
    char pgkw_str169[sizeof("serializable")];
    char pgkw_str170[sizeof("stdout")];
    char pgkw_str172[sizeof("language")];
    char pgkw_str173[sizeof("natural")];
    char pgkw_str177[sizeof("createrole")];
    char pgkw_str183[sizeof("class")];
    char pgkw_str193[sizeof("read")];
    char pgkw_str197[sizeof("desc")];
    char pgkw_str199[sizeof("role")];
    char pgkw_str207[sizeof("data")];
    char pgkw_str209[sizeof("conversion")];
    char pgkw_str211[sizeof("declare")];
    char pgkw_str213[sizeof("database")];
    char pgkw_str214[sizeof("also")];
    char pgkw_str225[sizeof("close")];
    char pgkw_str226[sizeof("cascade")];
    char pgkw_str228[sizeof("column")];
    char pgkw_str230[sizeof("dec")];
    char pgkw_str231[sizeof("collate")];
    char pgkw_str234[sizeof("connection")];
    char pgkw_str235[sizeof("localtime")];
    char pgkw_str237[sizeof("in")];
    char pgkw_str243[sizeof("is")];
    char pgkw_str244[sizeof("int")];
    char pgkw_str245[sizeof("true")];
    char pgkw_str246[sizeof("user")];
    char pgkw_str251[sizeof("order")];
    char pgkw_str252[sizeof("insert")];
    char pgkw_str253[sizeof("lock")];
    char pgkw_str254[sizeof("inner")];
    char pgkw_str258[sizeof("rollback")];
    char pgkw_str259[sizeof("intersect")];
    char pgkw_str260[sizeof("integer")];
    char pgkw_str262[sizeof("deallocate")];
    char pgkw_str264[sizeof("restrict")];
    char pgkw_str267[sizeof("delete")];
    char pgkw_str271[sizeof("document")];
    char pgkw_str272[sizeof("trigger")];
    char pgkw_str273[sizeof("lc_collate")];
    char pgkw_str275[sizeof("truncate")];
    char pgkw_str280[sizeof("scroll")];
    char pgkw_str283[sizeof("reassign")];
    char pgkw_str287[sizeof("current")];
    char pgkw_str291[sizeof("do")];
    char pgkw_str294[sizeof("current_time")];
    char pgkw_str300[sizeof("notnull")];
    char pgkw_str301[sizeof("end")];
    char pgkw_str302[sizeof("quote")];
    char pgkw_str303[sizeof("out")];
    char pgkw_str304[sizeof("current_role")];
    char pgkw_str306[sizeof("authorization")];
    char pgkw_str308[sizeof("cursor")];
    char pgkw_str310[sizeof("join")];
    char pgkw_str312[sizeof("into")];
    char pgkw_str313[sizeof("inout")];
    char pgkw_str314[sizeof("transaction")];
    char pgkw_str315[sizeof("outer")];
    char pgkw_str321[sizeof("current_schema")];
    char pgkw_str323[sizeof("noinherit")];
    char pgkw_str324[sizeof("isolation")];
    char pgkw_str325[sizeof("and")];
    char pgkw_str329[sizeof("decimal")];
    char pgkw_str330[sizeof("session_user")];
    char pgkw_str331[sizeof("local")];
    char pgkw_str332[sizeof("strip")];
    char pgkw_str338[sizeof("precision")];
    char pgkw_str340[sizeof("until")];
    char pgkw_str341[sizeof("nulls")];
    char pgkw_str343[sizeof("prepare")];
    char pgkw_str344[sizeof("preserve")];
    char pgkw_str345[sizeof("unlisten")];
    char pgkw_str346[sizeof("second")];
    char pgkw_str349[sizeof("rule")];
    char pgkw_str353[sizeof("all")];
    char pgkw_str354[sizeof("listen")];
    char pgkw_str356[sizeof("load")];
    char pgkw_str360[sizeof("greatest")];
    char pgkw_str361[sizeof("partition")];
    char pgkw_str362[sizeof("name")];
    char pgkw_str365[sizeof("relative")];
    char pgkw_str366[sizeof("names")];
    char pgkw_str368[sizeof("replace")];
    char pgkw_str370[sizeof("template")];
    char pgkw_str372[sizeof("cascaded")];
    char pgkw_str376[sizeof("like")];
    char pgkw_str378[sizeof("parser")];
    char pgkw_str379[sizeof("grant")];
    char pgkw_str380[sizeof("statement")];
    char pgkw_str385[sizeof("nocreateuser")];
    char pgkw_str389[sizeof("option")];
    char pgkw_str391[sizeof("cluster")];
    char pgkw_str392[sizeof("replica")];
    char pgkw_str393[sizeof("options")];
    char pgkw_str394[sizeof("indexes")];
    char pgkw_str395[sizeof("trusted")];
    char pgkw_str397[sizeof("distinct")];
    char pgkw_str401[sizeof("unencrypted")];
    char pgkw_str403[sizeof("operator")];
    char pgkw_str407[sizeof("then")];
    char pgkw_str410[sizeof("some")];
    char pgkw_str416[sizeof("nothing")];
    char pgkw_str418[sizeof("instead")];
    char pgkw_str419[sizeof("storage")];
    char pgkw_str421[sizeof("nologin")];
    char pgkw_str433[sizeof("share")];
    char pgkw_str435[sizeof("setof")];
    char pgkw_str437[sizeof("current_date")];
    char pgkw_str443[sizeof("null")];
    char pgkw_str444[sizeof("repeatable")];
    char pgkw_str445[sizeof("freeze")];
    char pgkw_str446[sizeof("handler")];
    char pgkw_str448[sizeof("plans")];
    char pgkw_str449[sizeof("double")];
    char pgkw_str451[sizeof("comment")];
    char pgkw_str452[sizeof("commit")];
    char pgkw_str454[sizeof("references")];
    char pgkw_str455[sizeof("nchar")];
    char pgkw_str457[sizeof("header")];
    char pgkw_str458[sizeof("oids")];
    char pgkw_str459[sizeof("location")];
    char pgkw_str460[sizeof("isnull")];
    char pgkw_str461[sizeof("union")];
    char pgkw_str462[sizeof("yes")];
    char pgkw_str464[sizeof("unique")];
    char pgkw_str466[sizeof("each")];
    char pgkw_str467[sizeof("chain")];
    char pgkw_str468[sizeof("after")];
    char pgkw_str470[sizeof("add")];
    char pgkw_str472[sizeof("check")];
    char pgkw_str473[sizeof("called")];
    char pgkw_str475[sizeof("leading")];
    char pgkw_str476[sizeof("old")];
    char pgkw_str477[sizeof("catalog")];
    char pgkw_str478[sizeof("char")];
    char pgkw_str480[sizeof("revoke")];
    char pgkw_str483[sizeof("configuration")];
    char pgkw_str484[sizeof("verbose")];
    char pgkw_str485[sizeof("partial")];
    char pgkw_str487[sizeof("insensitive")];
    char pgkw_str489[sizeof("prepared")];
    char pgkw_str493[sizeof("year")];
    char pgkw_str497[sizeof("schema")];
    char pgkw_str500[sizeof("disable")];
    char pgkw_str506[sizeof("array")];
    char pgkw_str508[sizeof("admin")];
    char pgkw_str511[sizeof("force")];
    char pgkw_str516[sizeof("login")];
    char pgkw_str517[sizeof("delimiters")];
    char pgkw_str521[sizeof("for")];
    char pgkw_str523[sizeof("current_user")];
    char pgkw_str525[sizeof("delimiter")];
    char pgkw_str526[sizeof("granted")];
    char pgkw_str532[sizeof("cycle")];
    char pgkw_str533[sizeof("characteristics")];
    char pgkw_str536[sizeof("character")];
    char pgkw_str537[sizeof("left")];
    char pgkw_str540[sizeof("drop")];
    char pgkw_str541[sizeof("varchar")];
    char pgkw_str542[sizeof("localtimestamp")];
    char pgkw_str545[sizeof("over")];
    char pgkw_str546[sizeof("input")];
    char pgkw_str549[sizeof("procedure")];
    char pgkw_str550[sizeof("version")];
    char pgkw_str551[sizeof("discard")];
    char pgkw_str552[sizeof("mode")];
    char pgkw_str556[sizeof("domain")];
    char pgkw_str557[sizeof("enum")];
    char pgkw_str560[sizeof("false")];
    char pgkw_str561[sizeof("password")];
    char pgkw_str566[sizeof("overlaps")];
    char pgkw_str568[sizeof("prior")];
    char pgkw_str569[sizeof("time")];
    char pgkw_str570[sizeof("between")];
    char pgkw_str571[sizeof("minute")];
    char pgkw_str573[sizeof("savepoint")];
    char pgkw_str574[sizeof("simple")];
    char pgkw_str577[sizeof("ilike")];
    char pgkw_str579[sizeof("wrapper")];
    char pgkw_str580[sizeof("next")];
    char pgkw_str581[sizeof("trim")];
    char pgkw_str582[sizeof("text")];
    char pgkw_str584[sizeof("right")];
    char pgkw_str585[sizeof("execute")];
    char pgkw_str587[sizeof("concurrently")];
    char pgkw_str590[sizeof("table")];
    char pgkw_str591[sizeof("definer")];
    char pgkw_str595[sizeof("value")];
    char pgkw_str597[sizeof("lancompiler")];
    char pgkw_str601[sizeof("current_timestamp")];
    char pgkw_str602[sizeof("smallint")];
    char pgkw_str603[sizeof("nowait")];
    char pgkw_str604[sizeof("values")];
    char pgkw_str606[sizeof("lc_ctype")];
    char pgkw_str607[sizeof("float")];
    char pgkw_str608[sizeof("owner")];
    char pgkw_str609[sizeof("sysid")];
    char pgkw_str610[sizeof("rows")];
    char pgkw_str611[sizeof("similar")];
    char pgkw_str612[sizeof("encoding")];
    char pgkw_str613[sizeof("trailing")];
    char pgkw_str617[sizeof("increment")];
    char pgkw_str618[sizeof("createdb")];
    char pgkw_str621[sizeof("position")];
    char pgkw_str623[sizeof("except")];
    char pgkw_str624[sizeof("extract")];
    char pgkw_str627[sizeof("exclusive")];
    char pgkw_str632[sizeof("only")];
    char pgkw_str636[sizeof("work")];
    char pgkw_str639[sizeof("tablespace")];
    char pgkw_str640[sizeof("object")];
    char pgkw_str642[sizeof("temp")];
    char pgkw_str650[sizeof("encrypted")];
    char pgkw_str651[sizeof("validator")];
    char pgkw_str659[sizeof("abort")];
    char pgkw_str660[sizeof("current_catalog")];
    char pgkw_str666[sizeof("always")];
    char pgkw_str672[sizeof("forward")];
    char pgkw_str673[sizeof("first")];
    char pgkw_str674[sizeof("privileges")];
    char pgkw_str676[sizeof("limit")];
    char pgkw_str677[sizeof("level")];
    char pgkw_str679[sizeof("minvalue")];
    char pgkw_str680[sizeof("procedural")];
    char pgkw_str682[sizeof("update")];
    char pgkw_str687[sizeof("default")];
    char pgkw_str688[sizeof("variadic")];
    char pgkw_str689[sizeof("defaults")];
    char pgkw_str691[sizeof("returning")];
    char pgkw_str692[sizeof("external")];
    char pgkw_str702[sizeof("deferrable")];
    char pgkw_str705[sizeof("hour")];
    char pgkw_str710[sizeof("invoker")];
    char pgkw_str724[sizeof("group")];
    char pgkw_str725[sizeof("hold")];
    char pgkw_str730[sizeof("boolean")];
    char pgkw_str731[sizeof("global")];
    char pgkw_str732[sizeof("security")];
    char pgkw_str737[sizeof("deferred")];
    char pgkw_str740[sizeof("valid")];
    char pgkw_str741[sizeof("owned")];
    char pgkw_str745[sizeof("committed")];
    char pgkw_str752[sizeof("uncommitted")];
    char pgkw_str756[sizeof("checkpoint")];
    char pgkw_str758[sizeof("match")];
    char pgkw_str760[sizeof("asymmetric")];
    char pgkw_str761[sizeof("type")];
    char pgkw_str768[sizeof("write")];
    char pgkw_str777[sizeof("placing")];
    char pgkw_str779[sizeof("unknown")];
    char pgkw_str788[sizeof("superuser")];
    char pgkw_str792[sizeof("using")];
    char pgkw_str795[sizeof("bit")];
    char pgkw_str799[sizeof("backward")];
    char pgkw_str801[sizeof("month")];
    char pgkw_str807[sizeof("interval")];
    char pgkw_str815[sizeof("absolute")];
    char pgkw_str817[sizeof("exists")];
    char pgkw_str824[sizeof("reindex")];
    char pgkw_str825[sizeof("fetch")];
    char pgkw_str828[sizeof("numeric")];
    char pgkw_str829[sizeof("search")];
    char pgkw_str833[sizeof("varying")];
    char pgkw_str836[sizeof("from")];
    char pgkw_str843[sizeof("foreign")];
    char pgkw_str848[sizeof("nocreatedb")];
    char pgkw_str859[sizeof("move")];
    char pgkw_str860[sizeof("full")];
    char pgkw_str865[sizeof("copy")];
    char pgkw_str870[sizeof("inherit")];
    char pgkw_str871[sizeof("symmetric")];
    char pgkw_str872[sizeof("inherits")];
    char pgkw_str874[sizeof("volatile")];
    char pgkw_str883[sizeof("function")];
    char pgkw_str892[sizeof("begin")];
    char pgkw_str911[sizeof("of")];
    char pgkw_str914[sizeof("implicit")];
    char pgkw_str919[sizeof("when")];
    char pgkw_str920[sizeof("where")];
    char pgkw_str923[sizeof("offset")];
    char pgkw_str925[sizeof("any")];
    char pgkw_str926[sizeof("immutable")];
    char pgkw_str930[sizeof("key")];
    char pgkw_str953[sizeof("index")];
    char pgkw_str955[sizeof("csv")];
    char pgkw_str959[sizeof("dictionary")];
    char pgkw_str977[sizeof("notify")];
    char pgkw_str983[sizeof("without")];
    char pgkw_str984[sizeof("before")];
    char pgkw_str991[sizeof("show")];
    char pgkw_str997[sizeof("mapping")];
    char pgkw_str1007[sizeof("overlay")];
    char pgkw_str1017[sizeof("primary")];
    char pgkw_str1022[sizeof("xmlelement")];
    char pgkw_str1023[sizeof("xmlconcat")];
    char pgkw_str1027[sizeof("both")];
    char pgkw_str1028[sizeof("xmlparse")];
    char pgkw_str1029[sizeof("aggregate")];
    char pgkw_str1035[sizeof("xmlforest")];
    char pgkw_str1039[sizeof("new")];
    char pgkw_str1040[sizeof("maxvalue")];
    char pgkw_str1066[sizeof("identity")];
    char pgkw_str1070[sizeof("day")];
    char pgkw_str1071[sizeof("if")];
    char pgkw_str1081[sizeof("unbounded")];
    char pgkw_str1086[sizeof("xmlroot")];
    char pgkw_str1088[sizeof("including")];
    char pgkw_str1114[sizeof("explain")];
    char pgkw_str1115[sizeof("xml")];
    char pgkw_str1119[sizeof("system")];
    char pgkw_str1120[sizeof("row")];
    char pgkw_str1128[sizeof("bigint")];
    char pgkw_str1131[sizeof("immediate")];
    char pgkw_str1136[sizeof("preceding")];
    char pgkw_str1140[sizeof("xmlserialize")];
    char pgkw_str1150[sizeof("with")];
    char pgkw_str1175[sizeof("nullif")];
    char pgkw_str1181[sizeof("vacuum")];
    char pgkw_str1184[sizeof("timestamp")];
    char pgkw_str1198[sizeof("whitespace")];
    char pgkw_str1207[sizeof("view")];
    char pgkw_str1240[sizeof("xmlpi")];
    char pgkw_str1251[sizeof("temporary")];
    char pgkw_str1331[sizeof("off")];
    char pgkw_str1393[sizeof("initially")];
    char pgkw_str1425[sizeof("excluding")];
    char pgkw_str1449[sizeof("by")];
    char pgkw_str1462[sizeof("substring")];
    char pgkw_str1541[sizeof("having")];
    char pgkw_str1579[sizeof("xmlattributes")];
    char pgkw_str1673[sizeof("family")];
    char pgkw_str1686[sizeof("binary")];
    char pgkw_str1783[sizeof("following")];
    char pgkw_str1787[sizeof("window")];
  };
static const struct pgkw_t pgkw_contents =
  {
    "set",
    "sequence",
    "rename",
    "treat",
    "reset",
    "returns",
    "at",
    "strict",
    "as",
    "enable",
    "start",
    "stable",
    "restart",
    "range",
    "assertion",
    "assignment",
    "server",
    "escape",
    "create",
    "analyze",
    "analyse",
    "recursive",
    "standalone",
    "case",
    "on",
    "cast",
    "action",
    "none",
    "zone",
    "createuser",
    "not",
    "session",
    "statistics",
    "or",
    "nosuperuser",
    "cache",
    "asc",
    "access",
    "else",
    "cost",
    "continue",
    "content",
    "select",
    "recheck",
    "cross",
    "release",
    "constraint",
    "constraints",
    "least",
    "no",
    "last",
    "to",
    "national",
    "coalesce",
    "real",
    "large",
    "alter",
    "stdin",
    "nocreaterole",
    "serializable",
    "stdout",
    "language",
    "natural",
    "createrole",
    "class",
    "read",
    "desc",
    "role",
    "data",
    "conversion",
    "declare",
    "database",
    "also",
    "close",
    "cascade",
    "column",
    "dec",
    "collate",
    "connection",
    "localtime",
    "in",
    "is",
    "int",
    "true",
    "user",
    "order",
    "insert",
    "lock",
    "inner",
    "rollback",
    "intersect",
    "integer",
    "deallocate",
    "restrict",
    "delete",
    "document",
    "trigger",
    "lc_collate",
    "truncate",
    "scroll",
    "reassign",
    "current",
    "do",
    "current_time",
    "notnull",
    "end",
    "quote",
    "out",
    "current_role",
    "authorization",
    "cursor",
    "join",
    "into",
    "inout",
    "transaction",
    "outer",
    "current_schema",
    "noinherit",
    "isolation",
    "and",
    "decimal",
    "session_user",
    "local",
    "strip",
    "precision",
    "until",
    "nulls",
    "prepare",
    "preserve",
    "unlisten",
    "second",
    "rule",
    "all",
    "listen",
    "load",
    "greatest",
    "partition",
    "name",
    "relative",
    "names",
    "replace",
    "template",
    "cascaded",
    "like",
    "parser",
    "grant",
    "statement",
    "nocreateuser",
    "option",
    "cluster",
    "replica",
    "options",
    "indexes",
    "trusted",
    "distinct",
    "unencrypted",
    "operator",
    "then",
    "some",
    "nothing",
    "instead",
    "storage",
    "nologin",
    "share",
    "setof",
    "current_date",
    "null",
    "repeatable",
    "freeze",
    "handler",
    "plans",
    "double",
    "comment",
    "commit",
    "references",
    "nchar",
    "header",
    "oids",
    "location",
    "isnull",
    "union",
    "yes",
    "unique",
    "each",
    "chain",
    "after",
    "add",
    "check",
    "called",
    "leading",
    "old",
    "catalog",
    "char",
    "revoke",
    "configuration",
    "verbose",
    "partial",
    "insensitive",
    "prepared",
    "year",
    "schema",
    "disable",
    "array",
    "admin",
    "force",
    "login",
    "delimiters",
    "for",
    "current_user",
    "delimiter",
    "granted",
    "cycle",
    "characteristics",
    "character",
    "left",
    "drop",
    "varchar",
    "localtimestamp",
    "over",
    "input",
    "procedure",
    "version",
    "discard",
    "mode",
    "domain",
    "enum",
    "false",
    "password",
    "overlaps",
    "prior",
    "time",
    "between",
    "minute",
    "savepoint",
    "simple",
    "ilike",
    "wrapper",
    "next",
    "trim",
    "text",
    "right",
    "execute",
    "concurrently",
    "table",
    "definer",
    "value",
    "lancompiler",
    "current_timestamp",
    "smallint",
    "nowait",
    "values",
    "lc_ctype",
    "float",
    "owner",
    "sysid",
    "rows",
    "similar",
    "encoding",
    "trailing",
    "increment",
    "createdb",
    "position",
    "except",
    "extract",
    "exclusive",
    "only",
    "work",
    "tablespace",
    "object",
    "temp",
    "encrypted",
    "validator",
    "abort",
    "current_catalog",
    "always",
    "forward",
    "first",
    "privileges",
    "limit",
    "level",
    "minvalue",
    "procedural",
    "update",
    "default",
    "variadic",
    "defaults",
    "returning",
    "external",
    "deferrable",
    "hour",
    "invoker",
    "group",
    "hold",
    "boolean",
    "global",
    "security",
    "deferred",
    "valid",
    "owned",
    "committed",
    "uncommitted",
    "checkpoint",
    "match",
    "asymmetric",
    "type",
    "write",
    "placing",
    "unknown",
    "superuser",
    "using",
    "bit",
    "backward",
    "month",
    "interval",
    "absolute",
    "exists",
    "reindex",
    "fetch",
    "numeric",
    "search",
    "varying",
    "from",
    "foreign",
    "nocreatedb",
    "move",
    "full",
    "copy",
    "inherit",
    "symmetric",
    "inherits",
    "volatile",
    "function",
    "begin",
    "of",
    "implicit",
    "when",
    "where",
    "offset",
    "any",
    "immutable",
    "key",
    "index",
    "csv",
    "dictionary",
    "notify",
    "without",
    "before",
    "show",
    "mapping",
    "overlay",
    "primary",
    "xmlelement",
    "xmlconcat",
    "both",
    "xmlparse",
    "aggregate",
    "xmlforest",
    "new",
    "maxvalue",
    "identity",
    "day",
    "if",
    "unbounded",
    "xmlroot",
    "including",
    "explain",
    "xml",
    "system",
    "row",
    "bigint",
    "immediate",
    "preceding",
    "xmlserialize",
    "with",
    "nullif",
    "vacuum",
    "timestamp",
    "whitespace",
    "view",
    "xmlpi",
    "temporary",
    "off",
    "initially",
    "excluding",
    "by",
    "substring",
    "having",
    "xmlattributes",
    "family",
    "binary",
    "following",
    "window"
  };
#define pgkw ((const char *) &pgkw_contents)
#ifdef __GNUC__
__inline
#endif
const struct PgKeyword *
pg_keyword_lookup_real (register const char *str, register unsigned int len)
{
  enum
    {
      TOTAL_KEYWORDS = 392,
      MIN_WORD_LENGTH = 2,
      MAX_WORD_LENGTH = 17,
      MIN_HASH_VALUE = 18,
      MAX_HASH_VALUE = 1787
    };

  static const struct PgKeyword wordlist[] =
    {
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 322 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str18, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 317 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str22, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1},
#line 294 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str28, PG_UNRESERVED_KEYWORD},
#line 357 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str29, PG_COL_NAME_KEYWORD},
#line 298 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str30, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 302 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str34, PG_UNRESERVED_KEYWORD},
      {-1},
#line 38 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str36, PG_UNRESERVED_KEYWORD},
#line 338 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str37, PG_UNRESERVED_KEYWORD},
#line 33 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str38, PG_RESERVED_KEYWORD},
      {-1},
#line 125 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str40, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 332 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str44, PG_UNRESERVED_KEYWORD},
#line 330 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str45, PG_UNRESERVED_KEYWORD},
#line 299 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str46, PG_UNRESERVED_KEYWORD},
      {-1}, {-1},
#line 284 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str49, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 35 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str53, PG_UNRESERVED_KEYWORD},
#line 36 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str54, PG_UNRESERVED_KEYWORD},
#line 319 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str55, PG_UNRESERVED_KEYWORD},
#line 130 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str56, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 82 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str65, PG_RESERVED_KEYWORD},
#line 29 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str66, PG_RESERVED_KEYWORD},
      {-1},
#line 28 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str68, PG_RESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1},
#line 289 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str73, PG_UNRESERVED_KEYWORD},
      {-1},
#line 331 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str75, PG_UNRESERVED_KEYWORD},
#line 54 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str76, PG_RESERVED_KEYWORD},
#line 252 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str77, PG_RESERVED_KEYWORD},
#line 55 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str78, PG_RESERVED_KEYWORD},
#line 19 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str79, PG_UNRESERVED_KEYWORD},
      {-1},
#line 235 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str81, PG_COL_NAME_KEYWORD},
#line 407 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str82, PG_UNRESERVED_KEYWORD},
#line 85 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str83, PG_UNRESERVED_KEYWORD},
#line 237 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str84, PG_RESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 320 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str92, PG_UNRESERVED_KEYWORD},
      {-1},
#line 334 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str94, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 257 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str101, PG_RESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 236 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str110, PG_UNRESERVED_KEYWORD},
#line 50 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str111, PG_UNRESERVED_KEYWORD},
#line 34 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str112, PG_RESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 18 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str120, PG_UNRESERVED_KEYWORD},
#line 124 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str121, PG_RESERVED_KEYWORD},
      {-1},
#line 81 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str123, PG_UNRESERVED_KEYWORD},
#line 78 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str124, PG_UNRESERVED_KEYWORD},
#line 77 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str125, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 316 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str129, PG_RESERVED_KEYWORD},
      {-1}, {-1},
#line 288 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str132, PG_UNRESERVED_KEYWORD},
      {-1},
#line 86 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str134, PG_TYPE_FUNC_NAME_KEYWORD},
      {-1}, {-1}, {-1},
#line 293 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str138, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 75 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str142, PG_RESERVED_KEYWORD},
      {-1},
#line 76 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str144, PG_UNRESERVED_KEYWORD},
#line 201 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str145, PG_COL_NAME_KEYWORD},
#line 229 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str146, PG_UNRESERVED_KEYWORD},
#line 197 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str147, PG_UNRESERVED_KEYWORD},
#line 354 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str148, PG_RESERVED_KEYWORD},
      {-1},
#line 224 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str150, PG_COL_NAME_KEYWORD},
#line 66 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str151, PG_COL_NAME_KEYWORD},
      {-1}, {-1},
#line 286 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str154, PG_COL_NAME_KEYWORD},
#line 196 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str155, PG_UNRESERVED_KEYWORD},
      {-1},
#line 26 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str157, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1},
#line 335 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str163, PG_UNRESERVED_KEYWORD},
      {-1}, {-1},
#line 231 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str166, PG_UNRESERVED_KEYWORD},
      {-1}, {-1},
#line 318 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str169, PG_UNRESERVED_KEYWORD},
#line 336 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str170, PG_UNRESERVED_KEYWORD},
      {-1},
#line 195 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str172, PG_UNRESERVED_KEYWORD},
#line 225 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str173, PG_TYPE_FUNC_NAME_KEYWORD},
      {-1}, {-1}, {-1},
#line 84 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str177, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1},
#line 63 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str183, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 285 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str193, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 113 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str197, PG_RESERVED_KEYWORD},
      {-1},
#line 305 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str199, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 98 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str207, PG_UNRESERVED_KEYWORD},
      {-1},
#line 79 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str209, PG_UNRESERVED_KEYWORD},
      {-1},
#line 104 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str211, PG_UNRESERVED_KEYWORD},
      {-1},
#line 99 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str213, PG_UNRESERVED_KEYWORD},
#line 25 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str214, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1},
#line 64 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str225, PG_UNRESERVED_KEYWORD},
#line 52 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str226, PG_UNRESERVED_KEYWORD},
      {-1},
#line 68 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str228, PG_RESERVED_KEYWORD},
      {-1},
#line 102 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str230, PG_COL_NAME_KEYWORD},
#line 67 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str231, PG_RESERVED_KEYWORD},
      {-1}, {-1},
#line 74 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str234, PG_UNRESERVED_KEYWORD},
#line 209 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str235, PG_RESERVED_KEYWORD},
      {-1},
#line 169 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str237, PG_RESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1},
#line 189 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str243, PG_TYPE_FUNC_NAME_KEYWORD},
#line 183 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str244, PG_COL_NAME_KEYWORD},
#line 360 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str245, PG_RESERVED_KEYWORD},
#line 373 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str246, PG_RESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1},
#line 258 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str251, PG_RESERVED_KEYWORD},
#line 181 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str252, PG_UNRESERVED_KEYWORD},
#line 212 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str253, PG_UNRESERVED_KEYWORD},
#line 177 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str254, PG_TYPE_FUNC_NAME_KEYWORD},
      {-1}, {-1}, {-1},
#line 306 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str258, PG_UNRESERVED_KEYWORD},
#line 185 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str259, PG_RESERVED_KEYWORD},
#line 184 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str260, PG_COL_NAME_KEYWORD},
      {-1},
#line 101 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str262, PG_UNRESERVED_KEYWORD},
      {-1},
#line 300 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str264, PG_UNRESERVED_KEYWORD},
      {-1}, {-1},
#line 110 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str267, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 119 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str271, PG_UNRESERVED_KEYWORD},
#line 358 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str272, PG_UNRESERVED_KEYWORD},
#line 198 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str273, PG_UNRESERVED_KEYWORD},
      {-1},
#line 361 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str275, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1},
#line 312 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str280, PG_UNRESERVED_KEYWORD},
      {-1}, {-1},
#line 287 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str283, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 88 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str287, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 118 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str291, PG_RESERVED_KEYWORD},
      {-1}, {-1},
#line 93 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str294, PG_RESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1},
#line 240 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str300, PG_TYPE_FUNC_NAME_KEYWORD},
#line 128 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str301, PG_RESERVED_KEYWORD},
#line 283 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str302, PG_UNRESERVED_KEYWORD},
#line 259 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str303, PG_COL_NAME_KEYWORD},
#line 91 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str304, PG_RESERVED_KEYWORD},
      {-1},
#line 39 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str306, PG_TYPE_FUNC_NAME_KEYWORD},
      {-1},
#line 96 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str308, PG_UNRESERVED_KEYWORD},
      {-1},
#line 192 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str310, PG_TYPE_FUNC_NAME_KEYWORD},
      {-1},
#line 187 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str312, PG_RESERVED_KEYWORD},
#line 178 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str313, PG_COL_NAME_KEYWORD},
#line 356 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str314, PG_UNRESERVED_KEYWORD},
#line 260 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str315, PG_TYPE_FUNC_NAME_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1},
#line 92 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str321, PG_TYPE_FUNC_NAME_KEYWORD},
      {-1},
#line 233 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str323, PG_UNRESERVED_KEYWORD},
#line 191 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str324, PG_UNRESERVED_KEYWORD},
#line 30 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str325, PG_RESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 103 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str329, PG_COL_NAME_KEYWORD},
#line 321 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str330, PG_RESERVED_KEYWORD},
#line 208 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str331, PG_UNRESERVED_KEYWORD},
#line 339 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str332, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1},
#line 274 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str338, PG_COL_NAME_KEYWORD},
      {-1},
#line 371 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str340, PG_UNRESERVED_KEYWORD},
#line 244 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str341, PG_UNRESERVED_KEYWORD},
      {-1},
#line 275 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str343, PG_UNRESERVED_KEYWORD},
#line 277 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str344, PG_UNRESERVED_KEYWORD},
#line 370 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str345, PG_UNRESERVED_KEYWORD},
#line 314 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str346, PG_UNRESERVED_KEYWORD},
      {-1}, {-1},
#line 309 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str349, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 24 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str353, PG_RESERVED_KEYWORD},
#line 206 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str354, PG_UNRESERVED_KEYWORD},
      {-1},
#line 207 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str356, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 156 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str360, PG_COL_NAME_KEYWORD},
#line 268 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str361, PG_UNRESERVED_KEYWORD},
#line 222 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str362, PG_UNRESERVED_KEYWORD},
      {-1}, {-1},
#line 292 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str365, PG_UNRESERVED_KEYWORD},
#line 223 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str366, PG_UNRESERVED_KEYWORD},
      {-1},
#line 296 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str368, PG_UNRESERVED_KEYWORD},
      {-1},
#line 348 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str370, PG_UNRESERVED_KEYWORD},
      {-1},
#line 53 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str372, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 204 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str376, PG_TYPE_FUNC_NAME_KEYWORD},
      {-1},
#line 266 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str378, PG_UNRESERVED_KEYWORD},
#line 154 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str379, PG_RESERVED_KEYWORD},
#line 333 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str380, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1},
#line 232 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str385, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 255 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str389, PG_UNRESERVED_KEYWORD},
      {-1},
#line 65 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str391, PG_UNRESERVED_KEYWORD},
#line 297 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str392, PG_UNRESERVED_KEYWORD},
#line 256 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str393, PG_UNRESERVED_KEYWORD},
#line 173 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str394, PG_UNRESERVED_KEYWORD},
#line 362 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str395, PG_UNRESERVED_KEYWORD},
      {-1},
#line 117 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str397, PG_RESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 366 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str401, PG_UNRESERVED_KEYWORD},
      {-1},
#line 254 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str403, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 351 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str407, PG_RESERVED_KEYWORD},
      {-1}, {-1},
#line 329 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str410, PG_RESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1},
#line 238 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str416, PG_UNRESERVED_KEYWORD},
      {-1},
#line 182 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str418, PG_UNRESERVED_KEYWORD},
#line 337 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str419, PG_UNRESERVED_KEYWORD},
      {-1},
#line 234 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str421, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1},
#line 324 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str433, PG_UNRESERVED_KEYWORD},
      {-1},
#line 323 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str435, PG_COL_NAME_KEYWORD},
      {-1},
#line 90 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str437, PG_RESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1},
#line 242 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str443, PG_RESERVED_KEYWORD},
#line 295 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str444, PG_UNRESERVED_KEYWORD},
#line 149 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str445, PG_TYPE_FUNC_NAME_KEYWORD},
#line 158 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str446, PG_UNRESERVED_KEYWORD},
      {-1},
#line 271 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str448, PG_UNRESERVED_KEYWORD},
#line 121 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str449, PG_UNRESERVED_KEYWORD},
      {-1},
#line 69 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str451, PG_UNRESERVED_KEYWORD},
#line 70 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str452, PG_UNRESERVED_KEYWORD},
      {-1},
#line 290 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str454, PG_RESERVED_KEYWORD},
#line 226 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str455, PG_COL_NAME_KEYWORD},
      {-1},
#line 160 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str457, PG_UNRESERVED_KEYWORD},
#line 250 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str458, PG_UNRESERVED_KEYWORD},
#line 211 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str459, PG_UNRESERVED_KEYWORD},
#line 190 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str460, PG_TYPE_FUNC_NAME_KEYWORD},
#line 367 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str461, PG_RESERVED_KEYWORD},
#line 406 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str462, PG_UNRESERVED_KEYWORD},
      {-1},
#line 368 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str464, PG_RESERVED_KEYWORD},
      {-1},
#line 123 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str466, PG_UNRESERVED_KEYWORD},
#line 57 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str467, PG_UNRESERVED_KEYWORD},
#line 22 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str468, PG_UNRESERVED_KEYWORD},
      {-1},
#line 20 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str470, PG_UNRESERVED_KEYWORD},
      {-1},
#line 61 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str472, PG_RESERVED_KEYWORD},
#line 51 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str473, PG_UNRESERVED_KEYWORD},
      {-1},
#line 200 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str475, PG_RESERVED_KEYWORD},
#line 251 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str476, PG_RESERVED_KEYWORD},
#line 56 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str477, PG_UNRESERVED_KEYWORD},
#line 58 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str478, PG_COL_NAME_KEYWORD},
      {-1},
#line 303 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str480, PG_UNRESERVED_KEYWORD},
      {-1}, {-1},
#line 73 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str483, PG_UNRESERVED_KEYWORD},
#line 383 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str484, PG_TYPE_FUNC_NAME_KEYWORD},
#line 267 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str485, PG_UNRESERVED_KEYWORD},
      {-1},
#line 180 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str487, PG_UNRESERVED_KEYWORD},
      {-1},
#line 276 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str489, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 405 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str493, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 311 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str497, PG_UNRESERVED_KEYWORD},
      {-1}, {-1},
#line 115 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str500, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1},
#line 32 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str506, PG_RESERVED_KEYWORD},
      {-1},
#line 21 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str508, PG_UNRESERVED_KEYWORD},
      {-1}, {-1},
#line 146 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str511, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1},
#line 213 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str516, PG_UNRESERVED_KEYWORD},
#line 112 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str517, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 145 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str521, PG_RESERVED_KEYWORD},
      {-1},
#line 95 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str523, PG_RESERVED_KEYWORD},
      {-1},
#line 111 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str525, PG_UNRESERVED_KEYWORD},
#line 155 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str526, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1},
#line 97 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str532, PG_UNRESERVED_KEYWORD},
#line 60 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str533, PG_UNRESERVED_KEYWORD},
      {-1}, {-1},
#line 59 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str536, PG_COL_NAME_KEYWORD},
#line 202 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str537, PG_TYPE_FUNC_NAME_KEYWORD},
      {-1}, {-1},
#line 122 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str540, PG_UNRESERVED_KEYWORD},
#line 380 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str541, PG_COL_NAME_KEYWORD},
#line 210 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str542, PG_RESERVED_KEYWORD},
      {-1}, {-1},
#line 261 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str545, PG_TYPE_FUNC_NAME_KEYWORD},
#line 179 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str546, PG_UNRESERVED_KEYWORD},
      {-1}, {-1},
#line 282 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str549, PG_UNRESERVED_KEYWORD},
#line 384 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str550, PG_UNRESERVED_KEYWORD},
#line 116 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str551, PG_UNRESERVED_KEYWORD},
#line 219 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str552, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 120 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str556, PG_UNRESERVED_KEYWORD},
#line 129 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str557, PG_UNRESERVED_KEYWORD},
      {-1}, {-1},
#line 139 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str560, PG_RESERVED_KEYWORD},
#line 269 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str561, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1},
#line 262 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str566, PG_TYPE_FUNC_NAME_KEYWORD},
      {-1},
#line 279 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str568, PG_UNRESERVED_KEYWORD},
#line 352 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str569, PG_COL_NAME_KEYWORD},
#line 43 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str570, PG_TYPE_FUNC_NAME_KEYWORD},
#line 217 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str571, PG_UNRESERVED_KEYWORD},
      {-1},
#line 310 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str573, PG_UNRESERVED_KEYWORD},
#line 327 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str574, PG_UNRESERVED_KEYWORD},
      {-1}, {-1},
#line 165 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str577, PG_TYPE_FUNC_NAME_KEYWORD},
      {-1},
#line 394 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str579, PG_UNRESERVED_KEYWORD},
#line 228 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str580, PG_UNRESERVED_KEYWORD},
#line 359 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str581, PG_COL_NAME_KEYWORD},
#line 350 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str582, PG_UNRESERVED_KEYWORD},
      {-1},
#line 304 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str584, PG_TYPE_FUNC_NAME_KEYWORD},
#line 134 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str585, PG_UNRESERVED_KEYWORD},
      {-1},
#line 72 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str587, PG_UNRESERVED_KEYWORD},
      {-1}, {-1},
#line 345 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str590, PG_RESERVED_KEYWORD},
#line 109 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str591, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 378 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str595, PG_UNRESERVED_KEYWORD},
      {-1},
#line 194 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str597, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 94 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str601, PG_RESERVED_KEYWORD},
#line 328 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str602, PG_COL_NAME_KEYWORD},
#line 241 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str603, PG_UNRESERVED_KEYWORD},
#line 379 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str604, PG_COL_NAME_KEYWORD},
      {-1},
#line 199 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str606, PG_UNRESERVED_KEYWORD},
#line 143 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str607, PG_COL_NAME_KEYWORD},
#line 265 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str608, PG_UNRESERVED_KEYWORD},
#line 343 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str609, PG_UNRESERVED_KEYWORD},
#line 308 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str610, PG_UNRESERVED_KEYWORD},
#line 326 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str611, PG_TYPE_FUNC_NAME_KEYWORD},
#line 126 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str612, PG_UNRESERVED_KEYWORD},
#line 355 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str613, PG_RESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 171 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str617, PG_UNRESERVED_KEYWORD},
#line 83 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str618, PG_UNRESERVED_KEYWORD},
      {-1}, {-1},
#line 272 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str621, PG_COL_NAME_KEYWORD},
      {-1},
#line 131 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str623, PG_RESERVED_KEYWORD},
#line 138 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str624, PG_COL_NAME_KEYWORD},
      {-1}, {-1},
#line 133 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str627, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1},
#line 253 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str632, PG_RESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 393 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str636, PG_UNRESERVED_KEYWORD},
      {-1}, {-1},
#line 346 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str639, PG_UNRESERVED_KEYWORD},
#line 246 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str640, PG_UNRESERVED_KEYWORD},
      {-1},
#line 347 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str642, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 127 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str650, PG_UNRESERVED_KEYWORD},
#line 377 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str651, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 16 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str659, PG_UNRESERVED_KEYWORD},
#line 89 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str660, PG_RESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1},
#line 27 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str666, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1},
#line 148 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str672, PG_UNRESERVED_KEYWORD},
#line 142 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str673, PG_UNRESERVED_KEYWORD},
#line 280 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str674, PG_UNRESERVED_KEYWORD},
      {-1},
#line 205 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str676, PG_RESERVED_KEYWORD},
#line 203 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str677, PG_UNRESERVED_KEYWORD},
      {-1},
#line 218 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str679, PG_UNRESERVED_KEYWORD},
#line 281 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str680, PG_UNRESERVED_KEYWORD},
      {-1},
#line 372 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str682, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1},
#line 105 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str687, PG_RESERVED_KEYWORD},
#line 381 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str688, PG_RESERVED_KEYWORD},
#line 106 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str689, PG_UNRESERVED_KEYWORD},
      {-1},
#line 301 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str691, PG_RESERVED_KEYWORD},
#line 137 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str692, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 107 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str702, PG_RESERVED_KEYWORD},
      {-1}, {-1},
#line 162 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str705, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1},
#line 188 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str710, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1},
#line 157 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str724, PG_RESERVED_KEYWORD},
#line 161 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str725, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1},
#line 47 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str730, PG_COL_NAME_KEYWORD},
#line 153 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str731, PG_UNRESERVED_KEYWORD},
#line 315 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str732, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1},
#line 108 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str737, PG_UNRESERVED_KEYWORD},
      {-1}, {-1},
#line 376 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str740, PG_UNRESERVED_KEYWORD},
#line 264 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str741, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 71 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str745, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 365 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str752, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 62 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str756, PG_UNRESERVED_KEYWORD},
      {-1},
#line 215 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str758, PG_UNRESERVED_KEYWORD},
      {-1},
#line 37 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str760, PG_RESERVED_KEYWORD},
#line 363 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str761, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 395 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str768, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 270 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str777, PG_RESERVED_KEYWORD},
      {-1},
#line 369 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str779, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 341 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str788, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 374 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str792, PG_RESERVED_KEYWORD},
      {-1}, {-1},
#line 46 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str795, PG_COL_NAME_KEYWORD},
      {-1}, {-1}, {-1},
#line 40 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str799, PG_UNRESERVED_KEYWORD},
      {-1},
#line 220 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str801, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1},
#line 186 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str807, PG_COL_NAME_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 17 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str815, PG_UNRESERVED_KEYWORD},
      {-1},
#line 135 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str817, PG_COL_NAME_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 291 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str824, PG_UNRESERVED_KEYWORD},
#line 141 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str825, PG_RESERVED_KEYWORD},
      {-1}, {-1},
#line 245 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str828, PG_COL_NAME_KEYWORD},
#line 313 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str829, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 382 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str833, PG_UNRESERVED_KEYWORD},
      {-1}, {-1},
#line 150 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str836, PG_RESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 147 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str843, PG_RESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1},
#line 230 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str848, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1},
#line 221 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str859, PG_UNRESERVED_KEYWORD},
#line 151 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str860, PG_TYPE_FUNC_NAME_KEYWORD},
      {-1}, {-1}, {-1}, {-1},
#line 80 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str865, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1},
#line 174 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str870, PG_UNRESERVED_KEYWORD},
#line 342 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str871, PG_RESERVED_KEYWORD},
#line 175 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str872, PG_UNRESERVED_KEYWORD},
      {-1},
#line 386 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str874, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 152 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str883, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 42 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str892, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 247 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str911, PG_UNRESERVED_KEYWORD},
      {-1}, {-1},
#line 168 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str914, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1},
#line 387 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str919, PG_RESERVED_KEYWORD},
#line 388 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str920, PG_RESERVED_KEYWORD},
      {-1}, {-1},
#line 249 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str923, PG_RESERVED_KEYWORD},
      {-1},
#line 31 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str925, PG_RESERVED_KEYWORD},
#line 167 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str926, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 193 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str930, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1},
#line 172 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str953, PG_UNRESERVED_KEYWORD},
      {-1},
#line 87 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str955, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 114 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str959, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 239 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str977, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1},
#line 392 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str983, PG_UNRESERVED_KEYWORD},
#line 41 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str984, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 325 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str991, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1},
#line 214 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str997, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 263 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1007, PG_COL_NAME_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 278 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1017, PG_RESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1},
#line 399 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1022, PG_COL_NAME_KEYWORD},
#line 398 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1023, PG_COL_NAME_KEYWORD},
      {-1}, {-1}, {-1},
#line 48 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1027, PG_RESERVED_KEYWORD},
#line 401 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1028, PG_COL_NAME_KEYWORD},
#line 23 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1029, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1},
#line 400 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1035, PG_COL_NAME_KEYWORD},
      {-1}, {-1}, {-1},
#line 227 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1039, PG_RESERVED_KEYWORD},
#line 216 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1040, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 163 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1066, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 100 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1070, PG_UNRESERVED_KEYWORD},
#line 164 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1071, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 364 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1081, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1},
#line 403 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1086, PG_COL_NAME_KEYWORD},
      {-1},
#line 170 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1088, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 136 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1114, PG_UNRESERVED_KEYWORD},
#line 396 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1115, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 344 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1119, PG_UNRESERVED_KEYWORD},
#line 307 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1120, PG_COL_NAME_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 44 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1128, PG_COL_NAME_KEYWORD},
      {-1}, {-1},
#line 166 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1131, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1},
#line 273 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1136, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 404 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1140, PG_COL_NAME_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 391 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1150, PG_RESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 243 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1175, PG_COL_NAME_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1},
#line 375 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1181, PG_UNRESERVED_KEYWORD},
      {-1}, {-1},
#line 353 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1184, PG_COL_NAME_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1},
#line 389 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1198, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 385 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1207, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1},
#line 402 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1240, PG_COL_NAME_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1},
#line 349 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1251, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 248 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1331, PG_RESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 176 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1393, PG_RESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1},
#line 132 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1425, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1},
#line 49 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1449, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1},
#line 340 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1462, PG_COL_NAME_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 159 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1541, PG_RESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1},
#line 397 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1579, PG_COL_NAME_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1},
#line 140 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1673, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1},
#line 45 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1686, PG_TYPE_FUNC_NAME_KEYWORD},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 144 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1783, PG_UNRESERVED_KEYWORD},
      {-1}, {-1}, {-1},
#line 390 "usual/pgutil_kwlookup.gp"
      {(int)(long)&((struct pgkw_t *)0)->pgkw_str1787, PG_RESERVED_KEYWORD}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = pg_keyword_lookup_hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register int o = wordlist[key].name;
          if (o >= 0)
            {
              register const char *s = o + pgkw;

              if (*str == *s && !strcmp (str + 1, s + 1))
                return &wordlist[key];
            }
        }
    }
  return 0;
}
