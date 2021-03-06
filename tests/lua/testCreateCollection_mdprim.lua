require "string"
require "utils"
require "config_mdprim"
require "createCollection"
require "dumpCollection"

local datadir = arg[1] or "../data/mdprim/"
local outputdir = arg[2] or '.'
local ctxconfig = getContextConfig( arg[3])
local storage = outputdir .. "/storage"
local docfiles = {"doc10.xml"}
local withrpc = (ctxconfig and ctxconfig.rpc) and true or false

ctx = strus_Context.new( ctxconfig)
local aclmap = {["1"]='A',["2"]='A',["3"]='A',["4"]='A',["5"]='A',["6"]='B',["7"]='B',["8"]='B',["9"]='B',["10"]='B'}

createCollection( ctx, storage, metadata_mdprim(), createDocumentAnalyzer_mdprim( ctx), true, datadir, docfiles, aclmap, withrpc)
local result = "collection dump:" .. dumpTree( dumpCollection( ctx, storage)) .. "\n"
local expected = [[
collection dump:
string config:
  string acl: "true"
  string cache: "524288K"
  string metadata:
    string cross: "UInt8"
    string docidx: "UInt32"
    string doclen: "UInt16"
    string factors: "UInt8"
    string hi: "UInt16"
    string lo: "UInt16"
  string path: "storage"
string docids:
  number 1: "1"
  number 2: "10"
  number 3: "2"
  number 4: "3"
  number 5: "4"
  number 6: "5"
  number 7: "6"
  number 8: "7"
  number 9: "8"
  number 10: "9"
string docs:
  string 1:
    string ACL: "A"
    string cross: 1
    string docid: "1"
    string docidx: 1
    string doclen: 0
    string factors: 0
    string hi: 0
    string lo: 0
  string 10:
    string ACL: "B"
    string cross: 1
    string docid: "10"
    string docidx: 10
    string doclen: 2
    string factors: 1
    string hi: 5
    string lo: 2
    string word: "2 5"
  string 2:
    string ACL: "A"
    string cross: 2
    string docid: "2"
    string docidx: 2
    string doclen: 1
    string factors: 0
    string hi: 2
    string lo: 2
    string word: "2"
  string 3:
    string ACL: "A"
    string cross: 3
    string docid: "3"
    string docidx: 3
    string doclen: 1
    string factors: 0
    string hi: 3
    string lo: 3
    string word: "3"
  string 4:
    string ACL: "A"
    string cross: 4
    string docid: "4"
    string docidx: 4
    string doclen: 2
    string factors: 1
    string hi: 2
    string lo: 2
    string word: "2 2"
  string 5:
    string ACL: "A"
    string cross: 5
    string docid: "5"
    string docidx: 5
    string doclen: 1
    string factors: 0
    string hi: 5
    string lo: 5
    string word: "5"
  string 6:
    string ACL: "B"
    string cross: 6
    string docid: "6"
    string docidx: 6
    string doclen: 2
    string factors: 1
    string hi: 3
    string lo: 2
    string word: "2 3"
  string 7:
    string ACL: "B"
    string cross: 7
    string docid: "7"
    string docidx: 7
    string doclen: 1
    string factors: 0
    string hi: 7
    string lo: 7
    string word: "7"
  string 8:
    string ACL: "B"
    string cross: 8
    string docid: "8"
    string docidx: 8
    string doclen: 3
    string factors: 2
    string hi: 2
    string lo: 2
    string word: "2 2 2"
  string 9:
    string ACL: "B"
    string cross: 9
    string docid: "9"
    string docidx: 9
    string doclen: 2
    string factors: 1
    string hi: 3
    string lo: 3
    string word: "3 3"
string nofdocs: 10
string stat:
  string dfchange:
    number 1:
      string increment: 5
      string type: "word"
      string value: "2"
    number 2:
      string increment: 3
      string type: "word"
      string value: "3"
    number 3:
      string increment: 2
      string type: "word"
      string value: "5"
    number 4:
      string increment: 1
      string type: "word"
      string value: "7"
  string nofdocs: 10
string terms:
  string 10:word (f):
    number 1:
      string pos: 1
      string value: "2"
    number 2:
      string pos: 2
      string value: "5"
  string 10:word (s):
    number 1:
      string firstpos: 1
      string tf: 1
      string value: "2"
    number 2:
      string firstpos: 2
      string tf: 1
      string value: "5"
  string 1:word (f): 
  string 1:word (s): 
  string 2:word (f):
    number 1:
      string pos: 1
      string value: "2"
  string 2:word (s):
    number 1:
      string firstpos: 1
      string tf: 1
      string value: "2"
  string 3:word (f):
    number 1:
      string pos: 1
      string value: "3"
  string 3:word (s):
    number 1:
      string firstpos: 1
      string tf: 1
      string value: "3"
  string 4:word (f):
    number 1:
      string pos: 1
      string value: "2"
    number 2:
      string pos: 2
      string value: "2"
  string 4:word (s):
    number 1:
      string firstpos: 1
      string tf: 2
      string value: "2"
  string 5:word (f):
    number 1:
      string pos: 1
      string value: "5"
  string 5:word (s):
    number 1:
      string firstpos: 1
      string tf: 1
      string value: "5"
  string 6:word (f):
    number 1:
      string pos: 1
      string value: "2"
    number 2:
      string pos: 2
      string value: "3"
  string 6:word (s):
    number 1:
      string firstpos: 1
      string tf: 1
      string value: "2"
    number 2:
      string firstpos: 2
      string tf: 1
      string value: "3"
  string 7:word (f):
    number 1:
      string pos: 1
      string value: "7"
  string 7:word (s):
    number 1:
      string firstpos: 1
      string tf: 1
      string value: "7"
  string 8:word (f):
    number 1:
      string pos: 1
      string value: "2"
    number 2:
      string pos: 2
      string value: "2"
    number 3:
      string pos: 3
      string value: "2"
  string 8:word (s):
    number 1:
      string firstpos: 1
      string tf: 3
      string value: "2"
  string 9:word (f):
    number 1:
      string pos: 1
      string value: "3"
    number 2:
      string pos: 2
      string value: "3"
  string 9:word (s):
    number 1:
      string firstpos: 1
      string tf: 2
      string value: "3"
string types:
  number 1: "word"
]]

verifyTestOutput( outputdir, result, expected)

