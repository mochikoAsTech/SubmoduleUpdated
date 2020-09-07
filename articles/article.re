
= サブモジュールとは？

ああサブモジュールよ、君の挙動が分からないんだ…！

//pagebreak

== Gitとは

本書はGitのサブモジュールの挙動が分からずに苦しむ人のための本なので、Gitとはなにか？についてや、@<code>{git pull}、@<code>{git clone}といった初歩的なgitコマンドについては解説しません。
「Gitについて何も知らないので1から学びたい」という方には、湊川あいさん@<fn>{llminatoll}の書籍がお勧めです。

//footnote[llminatoll][@<href>{https://twitter.com/llminatoll}]

 * わかばちゃんと学ぶ Git使い方入門
 ** @<href>{https://www.amazon.co.jp/dp/4863542178}

「お金をかけずにまずは無料で学びたい」という場合は、先ほどの本の元となったウェブ連載を読みましょう。書籍内容の序盤が体験できます。

 * マンガでわかるGit 第1話「Gitってなあに？」
 ** @<href>{https://next.rikunabi.com/journal/20160526_t12_iq/}

さらに最近は、SourceTreeのようにGUIを通してGitを使う方法だけでなく、コマンドでGitを使う方法が学べる「コマンド編」も連載されているそうです。

 * マンガでわかるGit ～コマンド編～ 第1話「リポジトリを作ってコミットしてみよう」
 ** @<href>{https://www.r-staffing.co.jp/engineer/entry/20190621_1}

Gitは付け焼き刃の操作だけを学ぶよりも、どういう仕組みで、どんな理屈で動いているのかをしっかり学んだ方が、結果としては理解の速度が上がります。@<fn>{know}
わかばちゃんと一緒にたくさん転んで、Gitを楽しく学んでみてください。

//footnote[know][Gitに限らず、どんなこともそうですよね。分かってはいるけれど、困ったらつい「Git いつ更新 調べる」のようにやりたいことベースで検索して、出てきたコマンドを叩いて、「なぜかは分からないけどできた！」みたいなことをしてしまうので、自分で書いていて耳が痛いです。]

== Gitのサブモジュールとは

サブモジュールとは、Gitの機能のひとつです。サブモジュールを使えば、あるプロジェクトのリポジトリを、別のリポジトリのサブディレクトリとして扱えるようになります。

急に「サブディレクトリとして扱える」と言われてもピンとこないと思うので、サブモジュールの便利な使用例をご紹介しましょう。

== サブモジュールの便利な使用例

筆者は、技術書の原稿をGitのリポジトリで管理しています。この原稿リポジトリの中には、実際の原稿ファイルや画像ファイルだけでなく、prh@<fn>{prh}という校正ツールがあり、その中には次のような「表記揺れを自動チェックするための正誤表」も含まれています。

//footnote[prh][ProofReading Helperの頭文字でprhです。@<href>{https://github.com/prh/prh}]

//cmd{
- expected: 筆者
  pattern:  著者
- expected: 本書
  pattern: 
    - この本
    - 本著
- expected: つたえる
  pattern:  伝える
- expected: 分かり
  pattern:  わかり
//}

筆者は本を一冊書くたびに、少しずつこの正誤表に新しい内容を追記しています。そのため新しい本の原稿リポジトリを作るときには、毎回ひとつ前の原稿リポジトリから、正誤表を含む校正ツールのディレクトリ@<fn>{dir}（@<code>{prh-rules}）をまるごとコピーしてくる必要がありました。

//footnote[dir][フォルダのこと。WindowsやMacではフォルダと呼ぶ方が馴染みがあると思いますが、本書ではGitのドキュメントやLinuxに倣ってディレクトリと呼びます。]

原稿リポジトリを作るたびに、いちいちコピーしてくるのは面倒です。さらに同時並行で色んな原稿を書いていると、あちらでの変更をこちらに持って来たり、今度はこちらでの変更をあちらに持って行ったりと、コピーペーストを繰り返す羽目になります。微妙に内容の違う正誤表が、古い原稿リポジトリに残っているのも気分的によくありません。ああ、@<strong>{校正ツールのディレクトリだけ別リポジトリに切り出せたら}いいのに…！

そんなときに便利なのがサブモジュールです！校正ツールのディレクトリ（@<code>{prh-rules}）だけをひとつのリポジトリとして切り出しておき、それぞれの原稿リポジトリでサブモジュールとして指定してやればいいのです。

先ほど「サブモジュールを使えば、あるプロジェクトのリポジトリを、別のリポジトリのサブディレクトリとして扱えるようになります。」と説明しましたが、これを実態に即した形にすると「サブモジュールを使えば、校正ツールのリポジトリを、それぞれの原稿リポジトリのサブディレクトリとして扱えるようになります。」となります。

サブモジュールは便利な一方で、構造が複雑になるので、思わぬトラブルの元となることがあります。なんとなくではなく、前述のように「たしかに！これは便利だ！」と思えるときに使いましょう。

== サブモジュールを使ってみよう

サブモジュールを理解するには、使ってみるのがいちばんです。まずはサブモジュールを使うための、メインのリポジトリから作ってみましょう。次の@<code>{git init main_project}というコマンドを叩くと、@<code>{main_project}というリポジトリのディレクトリが生成されます。

//cmd{
メインのリポジトリ（main_project）を作る
$ git init main_project
Initialized empty Git repository
 in C:/Users/mochikoAsTech/Documents/main_project/.git/
//}

main_projectが生成されました。（@<img>{SubmoduleUpdated_6}）@<fn>{hidden}

//footnote[hidden][@<code>{.git}が表示されない場合は、おそらく「ドットからはじまるファイルやフォルダは非表示」という設定になっています。Windowsなら「隠しファイルを表示する」にチェックを入れてください。Macなら@<code>{Command+Shift+.（ドット）}を押すことで表示されるようになります。]

//image[SubmoduleUpdated_6][main_projectというリポジトリのディレクトリができた][scale=0.8]{
//}

続いてメインリポジトリのサブモジュールとして、既にGitHub上に存在している別のリポジトリ@<fn>{meta}を追加してみましょう。

//cmd{
作ったメインリポジトリのディレクトリに移動する
$ cd main_project

サブモジュールとして「SubmoduleUpdated」というリポジトリを追加する
$ git submodule add https://github.com/mochikoAsTech/SubmoduleUpdated
//}

//footnote[meta][サブモジュールとして追加したのは、あなたが今読んでいるこの本の原稿リポジトリです。@<href>{https://github.com/mochikoAsTech/SubmoduleUpdated}]

今回はサブモジュールとして、本書の原稿リポジトリを追加してみました。（@<img>{SubmoduleUpdated_1}）@<fn>{url}

//image[SubmoduleUpdated_1][SubmoduleUpdatedがサブモジュールとして追加された][scale=0.8]{
//}

サブモジュールを追加すると、自動的に追加したSubmoduleUpdatedの中身をクローンしてくるため、こんな表示がされたと思います。

//footnote[url][今回はサブモジュールとしてGitHubのURLを指定しましたが、このような絶対パスのURLだけでなく、@<code>{git submodule add ../SubmoduleUpdated}のような相対パスでローカルのリポジトリを指定することも可能です。ただし相対パスで追加すると、サブモジュールのリモートリポジトリのURL（@<code>{remote.origin.url}）が@<code>{C:/Users/mochikoAsTech/Documents/SubmoduleUpdated}や@<code>{../SubmoduleUpdated}のようになります。特に理由が無ければリモートのURLで指定しておきましょう。]

//cmd{
Cloning into
 'C:/Users/mochikoAsTech/Documents/main_project/SubmoduleUpdated'...
remote: Enumerating objects: 251, done.
remote: Counting objects: 100% (251/251), done.
remote: Compressing objects: 100% (213/213), done.
Receiving objects:  97% (244/251), 2.25 MiB | 458.00 KiB/s(delta 103),
 reused 76 (delta 26), pack-reused 0
Receiving objects: 100% (251/251), 2.29 MiB | 455.00 KiB/s, done.
Resolving deltas: 100% (103/103), done.
//}

このときサブモジュール（@<code>{SubmoduleUpdated}）の中身はクローンしてきますが、サブモジュールのさらにサブモジュール（@<code>{prh-rules}）以下については再帰的にはクローンしてきてくれません。実際に@<code>{main_project/SubmoduleUpdated/prh-rules}を見てみると、中身はまだ空っぽです。（@<img>{SubmoduleUpdated_2}）

//image[SubmoduleUpdated_2][サブモジュールのサブモジュールはまだ中身が空っぽ][scale=0.8]{
//}

サブモジュールのサブモジュール以下についても、すべて中身を連れてきたい場合は、次のコマンドでサブモジュールを再帰的に初期化しておきましょう。このコマンドは、メインリポジトリである@<code>{main_project}ディレクトリで実行します。@<code>{SubmoduleUpdated}ディレクトリや@<code>{prh-rules}ディレクトリに移動して実行してはいけません。

//cmd{
サブモジュールを再帰的に初期化する
$ git submodule update --init --recursive
Submodule 'prh-rules' (https://github.com/mochikoAsTech/prh-rules)
 registered for path 'SubmoduleUpdated/prh-rules'
Cloning into
 'C:/Users/mochikoAsTech/Documents/main_project/SubmoduleUpdated/prh-rules'...
Submodule path 'SubmoduleUpdated/prh-rules': checked out
 'ec6d80a111881e28c6e8e5129cfa6a49b995830b'
//}

サブモジュールを再帰的に初期化したことで、サブモジュールのさらにサブモジュール（@<code>{prh-rules}）の中身もクローンできました。（@<img>{SubmoduleUpdated_3}）

//image[SubmoduleUpdated_3][サブモジュールのサブモジュールの中身も連れてこられた][scale=0.8]{
//}

なおサブモジュールを追加するときには、先ほどのように特にディレクトリ名を指定しなければ、サブモジュールのリポジトリ名（@<code>{SubmoduleUpdated}）がそのままディレクトリ名となります。ディレクトリ名を変えたいときは、次のパターンBのように末尾でディレクトリ名（@<code>{sub}）を指定します。するとディレクトリ名を「sub」にした状態でサブモジュールを追加できます。

//cmd{
パターンA. サブモジュールとして「SubmoduleUpdated」を追加する
$ git submodule add https://github.com/mochikoAsTech/SubmoduleUpdated

パターンB. ディレクトリ名を「sub」にした状態でサブモジュールを追加する
$ git submodule add https://github.com/mochikoAsTech/SubmoduleUpdated sub
//}

今回はパターンAのように「ディレクトリ名は特に指定しなかった」という前提で話を進めます。サブモジュールを追加してどうなったのか、@<code>{git status}コマンドでメインリポジトリの状態を確認してみましょう。

//cmd{
$ git status
On branch master

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)
        new file:   .gitmodules
        new file:   SubmoduleUpdated
//}

@<code>{new file}と表示されていることから、@<code>{.gitmodules}と@<code>{SubmoduleUpdated}の2つが、新しいファイルとして認識されていることが分かります。（@<img>{SubmoduleUpdated_4}）

//image[SubmoduleUpdated_4][.gitmodulesとSubmoduleUpdatedの2つが新しいファイルとして認識されている][scale=0.8]{
//}

サブモジュールを追加すると、このようにメインのリポジトリに@<code>{.gitmodules}というファイルが生まれます。これはテキスト形式のGitの設定ファイルです。テキストエディタで開くとこんなふうに、サブモジュールのディレクトリパスと、リモートのURLが書かれています。サブモジュールを複数追加した場合は、このファイルにサブモジュールの数だけ追記されていきます。

//cmd{
[submodule "SubmoduleUpdated"]
	path = SubmoduleUpdated
	url = https://github.com/mochikoAsTech/SubmoduleUpdated
//}

あなた以外の誰かが、この「サブモジュールを使っているメインリポジトリ」（@<code>{main_project}）をクローンした場合、Gitはこの@<code>{.gitmodules}というファイルに書かれた内容を元に、サブモジュールのパスや取得元を把握することになります。

続いて@<code>{git diff}コマンドでサブモジュール（@<code>{SubmoduleUpdated}）の変更前と変更後の差分を見てみましょう。まだコミットしていないファイルの差分が見たいので、@<code>{--cached}オプションを付ける必要があります。変更前の@<code>{--- /dev/null}は、このファイルが新たに作られたものであることを表しています。

//cmd{
$ git diff --cached SubmoduleUpdated
diff --git a/SubmoduleUpdated b/SubmoduleUpdated
new file mode 160000
index 0000000..6f47087
--- /dev/null
+++ b/SubmoduleUpdated
@@ -0,0 +1 @@
+Subproject commit 6f47087f1c9079ea6c677702da23ca040d0a13ed
//}

実際は@<code>{SubmoduleUpdated}はディレクトリであり、その中にはたくさんの原稿ファイルがあります。ですがメインのリポジトリからは、サブモジュールの中身を1つ1つ追跡するようなことはしません。代わりにこのサブディレクトリを、@<code>{+Subproject commit 6f47087f1c9079ea6c677702da23ca040d0a13ed}という1つのコミットとして記録していることが分かります。

メインのリポジトリを作って、そこにサブモジュールを追加する、という一通りの流れを体験してみました。ここで作った@<code>{main_project}というディレクトリは、この後はもう使用しませんのでまるごと消してしまっても構いません。

== サブモジュールを含むリポジトリをクローンしてこよう

さっきは「ローカルでリポジトリを作って、そこにサブモジュールを追加してみる」という流れを体験しました。今度は@<code>{prh-rules}というサブモジュールを含む、本著の原稿リポジトリを、メインリポジトリとしてGitHubからクローンしてみましょう。ローカルでのディレクトリ名は@<code>{sub_test}にします。

//cmd{
サブモジュールを使っているメインリポジトリをクローンしてくる
$ git clone https://github.com/mochikoAsTech/SubmoduleUpdated sub_test
//}

メインのリポジトリをクローンしてきたら、その中にある@<code>{prh-rules}というサブディレクトリを開いてみましょう。なんと中身は空っぽです。（@<img>{SubmoduleUpdated_5}）

//image[SubmoduleUpdated_5][サブモジュールの中身は空っぽ！][scale=0.8]{
//}

実はサブモジュールを含むメインのリポジトリをクローンすると、「サブモジュールが入っているはずのディレクトリ」は取得できるのですが、その時点ではその中身は空っぽなのです。

サブモジュールを初期化する@<code>{--init}オプションを付けて、@<code>{git submodule update}というコマンドを叩くことで、中身を連れてこられます。

//cmd{
サブモジュールの状態を初期化する（中身をクローンしてくる）
$ git submodule update --init
Submodule 'prh-rules' (https://github.com/mochikoAsTech/prh-rules)
 registered for path 'prh-rules'
Cloning into 'C:/Users/mochikoAsTech/Documents/SubmoduleUpdated/prh-rules'...
Submodule path 'prh-rules': checked out
 'f126abf930039a23d5e6ea9f418451fe69277ddb'
//}

これでサブモジュールである@<code>{prh-rules}の中身、つまり正誤表を含む校正ツールを一式持ってこられました。

== 最初からサブモジュールの中身も含めて全部連れてきたかった

メインのリポジトリをクローンしてきた直後に、空っぽの@<code>{prh-rules}を見ると「なんでサブモジュールの中身も一緒に連れてきてくれないの？！」という気持ちになります。@<fn>{okimochi}そういうときは@<code>{--recursive}オプションを付けてクローンすることで、最初からサブモジュールの中身も含めて全部まるっと連れてこられます。

//footnote[okimochi][みなさんがなるかどうかは分かりませんが筆者はなりました。なんで！サブモジュールの中身も一緒に！！連れてきてくれないの？！？！判子と朱肉はセットでしょ？！]

//cmd{
サブモジュールも含めて全部まるっとクローンしてくる
$ git clone --recursive https://github.com/mochikoAsTech/SubmoduleUpdated
//}

筆者はいちいちサブモジュールの有無を確認するのが面倒なので、リポジトリをクローンするときは基本的に@<code>{--recursive}オプションを付けています。

== メインリポジトリとサブモジュールは親子の関係

ところで1つのものをいろんな名前で呼ぶと混乱するので、ここから先の本書での呼び方を整理しておきましょう。

 * 親
 ** メインのリポジトリ（@<code>{SubmoduleUpdated}）のこと
 ** 内部にサブモジュールを含んでいる
 ** メインリポジトリやスーパープロジェクトと呼ばれることもある
 * 子
 ** 親から見たサブモジュールのリポジトリ（@<code>{prh-rules}）のこと
 ** 子（@<code>{prh-rules}）は、親（@<code>{SubmoduleUpdated}）の中にある
 ** つまり子は親のサブディレクトリである

メインリポジトリとサブモジュールは、親子のような関係になっています。
親は常に最新の子を見ている訳ではなく、子の特定のコミットを「子」として認識しています。@<fn>{child}

//footnote[child][「俺さ、大学進学のタイミングで家を出たから、うちの親の中ではハタチのままの俺で時間が止まってるんだよね。だからお盆に帰るとからあげとか山盛り出されてさ…俺もう30過ぎてるし、揚げ物そんなに食べられないんだけどなー」みたいな感じですね。あ、なんか急に切ない。]

たとえば、子のリポジトリではコミットが「A→B→C」と進んでいてCが最新ですが、親のリポジトリでは子の「Bのコミット」を指定しているとします。
この場合、親のリポジトリで@<code>{git submodule update}コマンドを叩くと、最新のCではなくBの時点の子をクローンしてきます。

つまり@<code>{git submodule update}は、「子を最新にして！」というコマンドではなく、「親が認識している時点（コミット）の子にアップデートして！」なのです。

一方、親のサブディレクトリである子に@<code>{cd}して、@<code>{git pull}コマンドを叩くと、親の認識に関係なく最新の「Cのコミット」を連れてきます。親の認識している「Bのコミット」を連れてきたいのか、それとも親の認識に関係なく最新の「Cのコミット」を連れてきたいのか、自分がしたいのはどちらなのか？を把握して、適切なgitコマンドを叩くことが大切です。

= サブモジュールのトラブルシューティング

サブモジュールで困ったらトラブル事例を見てみよう！

//pagebreak

== 【トラブル】サブモジュールを使っているか使っていないか確かめたい

「このプロジェクトってサブモジュール使ってたっけ？」と聞かれたけれど、「あの共通ライブラリはサブモジュールだったっけ…？それともComposerでパッケージ管理していたんだっけ…？」と分からなくなってしまった。
そんなときは親のリポジトリで@<code>{git submodule status}コマンドを叩いて、サブモジュールを使っているか否かを確かめてみましょう。サブモジュールの、いまの状態が表示されます。

//cmd{
サブモジュールを使っている場合
$ git submodule status
 ec6d80a111881e28c6e8e5129cfa6a49b995830b prh-rules (heads/master)

サブモジュールはあるが、まだ初期化されていない場合
$ git submodule status
-ec6d80a111881e28c6e8e5129cfa6a49b995830b prh-rules　←先頭にハイフンがある

サブモジュールを使っていない場合
$ git submodule status
　　　　　　　←何も表示されない
//}

== 【トラブル】git pullしただけなのにサブモジュールの差分が生まれた

あなたはいま親（@<code>{SubmoduleUpdated}）のmasterブランチにいます。
一緒に開発しているメンバーに「masterブランチを更新したから@<code>{git pull}してね！サブモジュール（@<code>{prh-rules}）も最新版になったよ」と言われました。幸い、手元でやりかけの作業はなかったので、「よし、じゃあ最新にするか！」と指示どおりに親で@<code>{git pull}コマンドを叩きました。

//cmd{
$ git pull
remote: Enumerating objects: 3, done.
remote: Counting objects: 100% (3/3), done.
remote: Compressing objects: 100% (1/1), done.
remote: Total 2 (delta 1), reused 2 (delta 1), pack-reused 0
Unpacking objects: 100% (2/2), 249 bytes | 14.00 KiB/s, done.
From https://github.com/mochikoAsTech/SubmoduleUpdated
   08bacf6..383f393  master     -> origin/master
Updating 08bacf6..383f393
Fast-forward
 prh-rules | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
//}

「よしよし、子（@<code>{prh-rules}）の更新をpullできたぞ！」と思って、確認のため@<code>{git status}を叩くと、なんとサブモジュールが更新されている、と出ます。

//cmd{
$ git status
On branch master
Your branch is up to date with 'origin/master'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   prh-rules (new commits)

no changes added to commit (use "git add" and/or "git commit -a")
//}

「いまgit pullして連れてきただけで、私は何のファイルも更新していないのに、なんで差分がでるの？」という気持ちになります。では@<code>{git diff}コマンドで、Gitが「なにを更新したと言い張っているのか？」を見てみましょう。

//cmd{
$ git diff
diff --git a/prh-rules b/prh-rules
index 782af14..f126abf 160000
--- a/prh-rules
+++ b/prh-rules
@@ -1 +1 @@
-Subproject commit 782af14a4dae78d62b591f7dab818826f721ca70　←10歳のサブモジュール
+Subproject commit f126abf930039a23d5e6ea9f418451fe69277ddb　←8歳のサブモジュール
//}

Chapter1で親を@<code>{git clone}したときのことを思い出してみましょう。あのときも、親を@<code>{git clode}しただけでは、子のディレクトリは空っぽで、@<code>{git submodule update --init}コマンドを叩いて初期化したことによって、初めてサブモジュールの中身を連れてくることができました。

それと同じで、@<code>{git pull}しただけでは、親が認識している子の年齢（コミット）が最新の10歳になるだけで、実際の子（サブモジュールのディレクトリの中身）は自動追従してこないので、8歳のままなのです。
つまり@<code>{git pull}したことによって、親の認識は「うちの子は8歳！」から「うちの子は10歳！」に変わったのですが、一方でそこにいる子供はまだアップデートされておらず8歳のままなので、親から見ると「10歳だったうちの子が8歳になってる！更新したんだね！差分があるよ！」という状態になっているのです。

親の認識に合わせて、サブモジュールの中身も10歳になってほしいので、@<code>{git submodule update}コマンドを叩いて、そこにいるサブモジュールを、「親が認識している子の年齢」、つまり10歳にアップデートしましょう。

//cmd{
サブモジュールを「親が認識している子の年齢（コミット）」にアップデートする
$ git submodule update
Submodule path 'prh-rules': checked out
 '782af14a4dae78d62b591f7dab818826f721ca70'　←10歳のサブモジュールを連れてきた
//}

@<code>{git pull}したことで、親が認識している子の年齢（コミット）が変わったんだから、そこはちゃんと付いてきてよ！と思いますが、そういうものなのです。

== 【トラブル】他のブランチへ移動しただけでサブモジュールがなぜか更新された

あなたはいまfeatureブランチで、「親の認識する子の年齢（コミット）を最新にする」という作業を行っています。もともと親が認識している子（サブモジュール）の年齢は8歳でしたが、実際の子は既に10歳を迎えていました。親のリポジトリでサブモジュールのディレクトリに移動した上で、@<code>{git pull}コマンドを叩いて子を10歳にしてやり、親の認識を「うちの子は10歳！」に改めた上で、それらの変更をfeatureブランチをコミット＆プッシュをしました。いまは「更新したけど未コミットなもの」は何もない状態です。

この状態で@<code>{git checkout master}して、masterブランチへ移動します。するとチェックアウトしてブランチを移動しただけなのに、@<code>{git status}を見るとこんな差分が表示されます。

//cmd{
$ git status
（中略）
        modified:   prh-rules (new commits)

no changes added to commit (use "git add" and/or "git commit -a")
//}

メイ、なにも変えてないもん！masterをチェックアウトしただけだもん！ほんとだよ！トトロいたもん！と叫びたくなりますが、@<code>{git diff}コマンドを叩いて、Gitが「なにを更新したと言い張っているのか？」を見てみましょう。

//cmd{
$ git diff
diff --git a/prh-rules b/prh-rules
index f126abf..782af14 160000
--- a/prh-rules
+++ b/prh-rules
@@ -1 +1 @@
-Subproject commit f126abf930039a23d5e6ea9f418451fe69277ddb　←8歳のサブモジュール
+Subproject commit 782af14a4dae78d62b591f7dab818826f721ca70　←10歳のサブモジュール
//}

そうです。@<code>{git checkout master}しただけでは、子の中身は自動追従してこないので10歳のままなのです。ですがmasterブランチでは、親が認識している子の年齢はまだ8歳です。そのため「うちの子が！！10歳になってる！！！8歳から10歳に更新したでしょ？！」となっているのです。

masterブランチで子の年齢を変えたい訳ではないので、こんなときは@<code>{git submodule update}コマンドを叩いて、そこにいるサブモジュールを、「親が認識している子の年齢」にアップデートしてあげましょう。

//cmd{
サブモジュールを「親が認識している子の年齢（コミット）」にアップデートする
$ git submodule update
Submodule path 'prh-rules': checked out
 'f126abf930039a23d5e6ea9f418451fe69277ddb'　←8歳のサブモジュールを連れてきた
//}

@<code>{update}というと、どうしても「古いものから新しいものにアップデートする」というイメージなので、「10歳から8歳の状態に戻す」ために@<code>{git submodule update}コマンドをたたくのは不思議な感じがするかもしれません。でもサブモジュールを、「親が認識している子の年齢」にアップデートするのが@<code>{git submodule update}なので、これでいいのです。

== 【トラブル】サブディレクトリでgit pullしたらなぜか更新された

あなたはいま親のmasterブランチにいます。
一緒に開発しているメンバーから「masterブランチで子の年齢（コミット）を9歳にしておいたから、masterブランチをpullしておいてね」と言われたので、指示どおりに@<code>{git pull}コマンドを叩きました。

//cmd{
$ git pull
remote: Enumerating objects: 3, done.
remote: Counting objects: 100% (3/3), done.
remote: Compressing objects: 100% (1/1), done.
remote: Total 2 (delta 1), reused 2 (delta 1), pack-reused 0
Unpacking objects: 100% (2/2), 249 bytes | 14.00 KiB/s, done.
From https://github.com/mochikoAsTech/SubmoduleUpdated
   08bacf6..383f393  master     -> origin/master
Updating 08bacf6..383f393
Fast-forward
 prh-rules | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
//}

「よしよし、子（@<code>{prh-rules}）の更新をpullできたぞ！」と思って、確認のため@<code>{git status}を叩くと、なんとサブモジュールが更新されている、と出ます。

//cmd{
$ git status
On branch master
Your branch is up to date with 'origin/master'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   prh-rules (new commits)

no changes added to commit (use "git add" and/or "git commit -a")
//}

@<code>{git diff}で確認したところ、どうやら親が認識している子の年齢（コミット）は9歳になったのに、そこにいる子は8歳のままなので、更新したと見なされて差分が出ているようです。

//cmd{
$ git diff
diff --git a/prh-rules b/prh-rules
index 4ac24b6..ec6d80a 160000
--- a/prh-rules
+++ b/prh-rules
@@ -1 +1 @@
-Subproject commit 4ac24b6fd2df37053900fe21f611b9b4131b1941　←9歳のサブモジュール
+Subproject commit ec6d80a111881e28c6e8e5129cfa6a49b995830b　←8歳のサブモジュール
//}

「子を最新にすればいいんでしょ！」と思ったあなたは、子のディレクトリに移動して、@<code>{git pull}を叩きました。
そして再び@<code>{git diff}で確認してみたのですが、なんと差分はなくなっていません。親が認識している子の年齢（コミット）は9歳なのに、最新版の子を@<code>{git pull}した結果、9歳を飛び越えていきなり最新の10歳を連れてきてしまったようです。親が「9歳のはずのうちの子が！！10歳になってる！！！更新したでしょ？！」と驚いています。

//cmd{
$ git diff
diff --git a/prh-rules b/prh-rules
index 4ac24b6..4690206 160000
--- a/prh-rules
+++ b/prh-rules
@@ -1 +1 @@
-Subproject commit 4ac24b6fd2df37053900fe21f611b9b4131b1941　←9歳のサブモジュール
+Subproject commit 4690206e805b34e63580e0506b476dcdcc3d4c27　←10歳のサブモジュール
//}

親の認識に合わせて、サブモジュールの中身には9歳になってほしいので、この場合は親のディレクトリで@<code>{git submodule update}コマンドを叩きましょう。

//cmd{
サブモジュールを「親が認識している子の年齢（コミット）」にアップデートする
$ git submodule update
Submodule path 'prh-rules': checked out
 '4ac24b6fd2df37053900fe21f611b9b4131b1941'　←9歳のサブモジュールを連れてきた
//}

これでサブモジュールの中身は「親が認識している子の年齢（コミット）」になり、意図しない差分もなくなりました。

== 手間なくラクにサブモジュールを更新するには

話をまとめると、親が認識している年齢（コミット）の子を連れてきたいときには、@<code>{cd}コマンドでサブモジュールに移動して、そこで@<code>{git pull}してはいけません。親の認識にかかわらず、子が最新版になってしまいます。最新版が10歳で、親の認識も10歳であれば@<strong>{たまたま}問題は発生しませんが、いずれにしてもこの方法はお勧めしません。

親で@<code>{git pull}した後、親（メインプロジェクト）が認識している、子（サブモジュール）の状態にアップデートしたければ、@<code>{git submodule update}を使いましょう。

//cmd{
サブモジュールを「親が認識している子の年齢（コミット）」にアップデートする
$ git submodule update
//}

サブモジュールの中にさらにサブモジュールがいる場合は、@<code>{--recursive}オプションを付けた@<code>{git submodule update --recursive}を叩けば、入れ子になっているサブモジュールも再帰的にアップデートしてくれます。

//cmd{
サブモジュールや、サブモジュールのサブモジュールを再帰的にアップデートする
$ git submodule update --recursive
//}

@<code>{git pull}コマンドを叩いてから、さらに@<code>{git submodule update --recursive}コマンドを叩くのは面倒だな、という場合は@<code>{git pull && git submodule update --recursive}でひとまとめにしてもかまいません。

ですが@<code>{git pull && git submodule update --recursive}を叩くくらいなら、代わりに、@<code>{git pull --recurse-submodules}でも同じ結果が得られます。さらに@<code>{git config submodule.recurse true}コマンドを叩いて、@<code>{submodule.recurse}@<fn>{config}を有効にしてしまえば、以降は@<code>{git pull}するだけで、ついでにサブモジュールも「親が認識している子の年齢（コミット）」で再帰的にアップデートしてもらえるようになります。

//cmd{
プルしたついでにサブモジュールを再帰的にアップデートする
$ git pull --recurse-submodules
//}

サブモジュールの挙動を理解して、サブモジュールを手間なくラクに「親が認識している子の年齢（コミット）」にアップデートしましょう。

//footnote[config][ただし@<code>{submodule.recurse}をtrueにすると、@<code>{pull}だけでなく@<code>{--recurse-submodules}オプションがあるすべてのコマンド (checkout、fetch、grep、pull、push、read-tree、reset、restore、switch) に影響が及びますので注意してください。@<href>{https://git-scm.com/docs/git-config#Documentation/git-config.txt-submodulerecurse}]
