
= ああサブモジュール、君のこと（挙動）が分からない

== Gitとは

本書はGitのサブモジュールの挙動が分からずに苦しむ人のための本なので、Gitそのものについては解説しません。
「Gitについて何も知らないので1から学びたい」という方には、湊川あいさんの書籍がお勧めです。

 * わかばちゃんと学ぶ Git使い方入門
 ** @<href>{https://www.amazon.co.jp/dp/4863542178}

「お金をかけずにまずは無料で学びたい」という場合は、先ほどの本の元となったウェブ連載を読みましょう。書籍内容の序盤が体験できます。

 * マンガでわかるGit 第1話「Gitってなあに？」
 ** @<href>{https://next.rikunabi.com/journal/20160526_t12_iq/}

さらにSourceTreeのようなGUIを通してGitを使う方法だけでなく、コマンドでGitを使う方法が学べる「コマンド編」も連載されているそうです。

 * マンガでわかるGit ～コマンド編～ 第1話「リポジトリを作ってコミットしてみよう」
 ** @<href>{https://www.r-staffing.co.jp/engineer/entry/20190621_1}

Gitは付け焼き刃の操作だけを学ぶよりも、どういう仕組みで、どんな理屈で動いているのかをしっかり学んだ方が、結果としては理解の速度が上がります。
わかばちゃんと一緒にたくさん転んで、Gitを楽しく学んでみてください。

== Gitのサブモジュールとは

サブモジュールとは、Gitの機能のひとつです。サブモジュールを使えば、あるプロジェクトのリポジトリを、別のリポジトリのサブディレクトリとして扱えるようになります。

急に「サブディレクトリ」と言われてもピンとこないと思うので、便利な使用例をご紹介しましょう。

=== サブモジュールの便利な使用例

筆者は、技術書の原稿をGitのリポジトリで管理しています。この原稿リポジトリの中には、実際の原稿ファイルや画像ファイルだけでなく、prh@<fn>{prh}という校正ツールがあり、その中には次のように「表記揺れを自動チェックするための正誤表」が含まれています。

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

筆者は本を一冊書くたびに、少しずつこの正誤表に新しい内容を追記しています。そのため新しい本の原稿リポジトリを作るたびに、ひとつ前の原稿リポジトリから、正誤表を含む校正ツールのフォルダ（@<code>{prh-rules}）をまるごとコピーしてくる必要がありました。

コピーは面倒くさいですし、さらに同時並行で色んな原稿を書いていると、あちらでの変更をこちらに持って来たり、今度はこちらでの変更をあちらに持って行ったりと、Gitを使っているとは思えないようなコピーペーストを繰り返す羽目になります。微妙に内容の違う正誤表があちこちにあるのは気分的にもよくありません。ああ、校正ツールのフォルダだけ別リポジトリに切り出せたらいいのに…！

そんなときに便利なのがサブモジュールです！校正ツールのフォルダ（@<code>{prh-rules}）だけをひとつのリポジトリとして用意しておき、それぞれの原稿リポジトリでサブモジュールとして指定してやればいいのです。

先ほど「サブモジュールを使えば、あるプロジェクトのリポジトリを、別のリポジトリのサブディレクトリとして扱えるようになります。」と説明しましたが、これを実態に即した形で説明すると「サブモジュールを使えば、校正ツールのリポジトリを、それぞれの原稿リポジトリのサブディレクトリとして扱えるようになります。」となります。

サブモジュールは便利な一方で、挙動を理解せずに使うとトラブルの元になりやすいです。前述のように「たしかに！これは便利だ！」と心の底から思えるときにだけ使うのがお勧めです。

== サブモジュールの作り方

まず親を作ります。

//cmd{
メインのリポジトリ（main_project）を作る
$ git init main_project
//}

続いてメインのリポジトリのサブモジュールとして、既に存在している別のリポジトリを追加します。

//cmd{
作ったリポジトリのディレクトリに移動する
$ cd main_project

サブモジュールとして「SubmoduleUpdated」というリポジトリを追加する
$ git submodule add https://github.com/mochikoAsTech/SubmoduleUpdated
//}

今回はサブモジュールとして、本書の原稿リポジトリを追加してみました。@<fn>{url}追加したSubmoduleUpdatedをクローンしてくるため、こんな表示がされたと思います。このときサブモジュールの中身はクローンしてきますが、サブモジュールのさらにサブモジュール以下については再帰的にはクローンしてきてくれないので注意が必要です。

//footnote[url][今回はGitHubのURLを指定しましたが、このような絶対のURLに限らず、@<code>{git submodule add ../SubmoduleUpdated}のような相対パス、サブモジュールとしてローカルのリポジトリを指定することも可能です。ただし相対パスで追加すると、サブモジュールのリモートリポジトリのURL（@<code>{remote.origin.url}）が@<code>{C:/Users/mochikoAsTech/Documents/SubmoduleUpdated}や@<code>{../SubmoduleUpdated}のようになってしまうので、特に理由が無ければリモートのURLで指定する方がお勧めです。]

//cmd{
$ git submodule add https://github.com/mochikoAsTech/SubmoduleUpdated
Cloning into 'C:/Users/mochikoAsTech/Documents/main_project/SubmoduleUpdated'...
remote: Enumerating objects: 162, done.
remote: Counting objects: 100% (162/162), done.
remote: Compressing objects: 100% (143/143), done.
remote: Total 162 (delta 43), reused 26 (delta 7), pack-reused 0 eceiving objects:  93% (151/162), 308.00 KReceiving objects: 100% (162/162), 308.00 KiB | 604.00 KiB/s
objects: 100% (162/162), 518.33 KiB | 772.00 KiB/s, done.
Resolving deltas: 100% (43/43), done.
//}

なおサブモジュールを追加するとき、先ほどのように特にディレクトリ名を指定しないと、サブモジュールのリポジトリ名（@<code>{SubmoduleUpdated}）がそのままディレクトリ名となります。（@<img>{SubmoduleUpdated_1}）

//image[SubmoduleUpdated_1][SubmoduleUpdatedがサブモジュールとして追加された][scale=0.8]{
//}

ディレクトリ名を変えたいときは、次のように末尾でディレクトリ名（@<code>{sub}）を指定します。するとディレクトリ名を「sub」にした状態でサブモジュールを追加できます。

//cmd{
git submodule add https://github.com/mochikoAsTech/SubmoduleUpdated submodule
//}

サブモジュールを追加してどうなったのか、@<code>{git status}でメインリポジトリの状態を確認してみましょう。

//cmd{
$ git status
On branch master

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)
        new file:   .gitmodules
        new file:   SubmoduleUpdated
//}

@<code>{.gitmodules}と@<code>{SubmoduleUpdated}の2つが、新しいファイルとして認識されています。

サブモジュールを追加すると、このように親のリポジトリに@<code>{.gitmodules}というファイルが生まれます。これはテキスト形式の設定ファイルで、テキストエディタで開くと、こんなふうにサブモジュールのディレクトリパスと、リモートのURLが書かれています。サブモジュールを複数追加すると、このファイルにその分だけ追記されていきます。

//cmd{
[submodule "SubmoduleUpdated"]
	path = SubmoduleUpdated
	url = https://github.com/mochikoAsTech/SubmoduleUpdated
//}

他の人がサブモジュールを使っているメインリポジトリをクローンすると、Gitはこのファイルに書かれた内容を元に、サブモジュールの取得元を把握することになります。

続いて@<code>{git diff}で@<code>{SubmoduleUpdated}を見てみましょう。コミット前のファイルの差分を見たいので、@<code>{--cached}オプションを付ける必要があります。

変更前の@<code>{--- /dev/null}は、このファイルが新たに作られたものであることを表しています。

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

実際はSubmoduleUpdatedはディレクトリであり、その中にはたくさんの原稿ファイルがあります。ですがメインのリポジトリからは、サブモジュールの中身を1つ1つ追跡するようなことはしません。代わりにこのサブディレクトリを、親から見た「子の年齢」のような@<code>{+Subproject commit 6f47087f1c9079ea6c677702da23ca040d0a13ed}という1つのコミットとして記録していることが分かります。

== サブモジュールを含むリポジトリをクローンしてこよう

今度は実際に@<code>{prh-rules}というサブモジュールを使っている原稿リポジトリをクローンしてみましょう。

//cmd{
サブモジュールを使っているメインリポジトリをクローンしてくる
$ git clone https://github.com/mochikoAsTech/SubmoduleUpdated
//}

@<code>{prh-rules}というディレクトリを開いてみましょう。なんと中身は空っぽです。実はサブモジュールを含むメインのリポジトリをクローンすると、「サブモジュールが入っているはずのディレクトリ」は取得できるのですが、最初の時点ではその中身は空っぽなのです。

サブモジュールを初期化する@<code>{--init}オプションを付けて、@<code>{git submodule update}することで、中身を連れてこられます。

//cmd{
サブモジュールの状態を初期化する（中身を連れてくる）
$ git submodule update --init
Submodule 'prh-rules' (https://github.com/mochikoAsTech/prh-rules) registered for path 'prh-rules'
Cloning into 'C:/Users/mochikoAsTech/Documents/SubmoduleUpdated/prh-rules'...
Submodule path 'prh-rules': checked out 'f126abf930039a23d5e6ea9f418451fe69277ddb'
//}

これで正誤表を含む校正ツールを一式持ってこられました。

== 最初からサブモジュールの中身も含めて全部連れてきたかった

空っぽの@<code>{prh-rules}を見ると「使いたいからサブモジュールとして指定してるの！なんでサブモジュールの中身も一緒に連れてきてくれないの！！」という気持ちになります。そういうときは@<code>{--recursive}オプションを付けてクローンすることで、最初からサブモジュールの中身も含めて全部まるっと連れてこられます。

//cmd{
サブモジュールも含めて全部まるっとクローンしてくる
$ git clone --recursive https://github.com/mochikoAsTech/SubmoduleUpdated
//}

筆者はいちいちサブモジュールの有無を確認するのが面倒なので、リポジトリをクローンするときは基本的に@<code>{--recursive}オプションを付けています。

== 親子の関係

Gitのメインリポジトリを親、サブモジュールを子だとします。

サブモジュールのリポジトリではコミットが「A→B→C」で進んでいて、けれど親のリポジトリではまだBを参照しているとします。
この場合、親のリポジトリで@<code>{git submodule update}したら、サブモジュールはBを引っ張ってきます。

@<code>{git submodule update}とは、「子のサブモジュールを最新にしておくれ」ではなく、「"親が指定している子のコミット"に更新しておくれ」なのです。

== git pullしただけなのに差分が出た

あなたはいまmasterブランチにいます。他の人から「masterを更新したから@<code>{git pull}してね！サブモジュールも最新版になったよ」と言われました。幸い、手元でやりかけの作業はなかったので@<code>{git status}を叩いても、更新してあるファイルはありません。よし、じゃあ最新の状態にするか！と@<code>{git pull}を叩いたところ、なんとサブモジュールが更新されたよ！！差分があるよ！！コミットしなよ！！という表示がわらわら出てきました。

いったい何が起きたのでしょう？masterブランチで@<code>{git pull}を叩いただけで、なんのファイルも更新していないのに、なぜ更新されたファイルがわらわら出てくるのでしょうか？

@<code>{git clone}したときのことを思い出してください。あのときも、@<code>{git clode}しただけでは、サブモジュールのディレクトリは空っぽで、@<code>{git submodule update --init}を叩いたことで初めてサブモジュールの中身を連れてくることができました。

実は@<code>{git pull}しただけでは、メインのリポジトリが指しているサブモジュールのコミットが最新版になるだけで、実際のディレクトリの中身は連れてこられないのです。@<code>{git pull}したことによって、親の認識は「うちの子は8歳！」から「うちの子は10歳！」に変わったのですが、一方でそこにいる子供はまだアップデートされておらず8歳のままなので、親から見ると「10歳だったうちの子が8歳になってる！更新したんだね！差分だ！」という状態になっているのです。

そんなときは深呼吸をして、@<code>{git submodule update}を叩きましょう。そこにいるサブモジュールを、「親が認識している子の年齢」にアップデートしてくれます。

//cmd{
メインプロジェクトが認識しているサブモジュールの状態にアップデートする
$ git submodule update
//}

== git checkoutしただけなのに差分が出た

あなたはいまfeatureブランチで、親の認識するサブモジュールのバージョンを最新版にするという作業を行っています。もともと親が認識しているサブモジュールの年齢は8歳でしたが、実際のサブモジュールは既に10歳を迎えていました。メインのリポジトリでもサブモジュールを@<code>{git pull}して10歳にしてやり、親が認識しているサブモジュールの年齢を10歳に更新した上で、featureブランチをコミット＆プッシュをしました。いまは「更新したけど未コミットなもの」は何もない状態です。

この状態で@<code>{git checkout master}して、masterブランチへ移動します。するとチェックアウトしてブランチを移動しただけなのに、@<code>{git status}を見るとこんな差分が表示されます。

//cmd{
$ git status
（中略）
        modified:   prh-rules (new commits)

no changes added to commit (use "git add" and/or "git commit -a")
//}

メイ、なにも変えてないもん！masterをチェックアウトしただけだもん！ほんとだもん！と叫びたくなりますが、@<code>{git diff}でGitが「なにを更新したと言い張っているのか？」を見てみましょう。

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

そうです。@<code>{git checkout}しただけでは、サブモジュールの中身は自動追従してこないので、サブモジュールの中身は10歳のままです。でもmasterブランチでは、親が認識しているサブモジュールの年齢はまだ8歳です。そのため「子供が！！10歳になってる！！！8歳から10歳に更新したでしょ？！」となっているのです。

masterブランチで何かを変えたい訳ではないので、こんなときは@<code>{git submodule update}を叩いて、そこにいるサブモジュールを、「親が認識している子の年齢」にアップデートしましょう。

//cmd{
メインプロジェクトが認識しているサブモジュールの状態にアップデートする
$ git submodule update
Submodule path 'prh-rules': checked out 'f126abf930039a23d5e6ea9f418451fe69277ddb'　←8歳のサブモジュールを連れてきた
//}

updateというと、どうしても「古いものから新しいものにアップデートする」というイメージなので、「10歳から8歳の状態に戻す」ために@<code>{git submodule update}をたたくのは不思議な感じがするかもしれません。でもサブモジュールを、「親が認識している子の年齢」にアップデートするのが@<code>{git submodule update}なので、これでいいのです。

== サブモジュールでgit pullしただけなのに差分が出た

あなたはいまメインリポジトリのmasterブランチにいます。
一緒に開発しているメンバーから「サブモジュールのバージョン上げたから、masterブランチをpullしておいてね」と言われました。

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

よしよし、prh-rulesの更新をpullできたぞ！と思って、確認のため@<code>{git status}を叩くと、なんとサブモジュールが更新されている、と出ます。

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

いまgit pullして連れてきたのに、なんで差分がでるの？私は更新してないよ？？という気持ちになります。では@<code>{git diff}でGitが「なにを更新したと言い張っているのか？」を見てみましょう。

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

そうです。@<code>{git pull}したことによって、親が認識している子供の年齢は10歳になったのですが、サブモジュールの中身は自動追従してこないので8歳のままなのです。それによって「子供が10歳から8歳になってる！あなた更新したわね！」となっているのです。

親の認識に合わせて、サブモジュールの中身も10歳になってほしいので、@<code>{git submodule update}を叩いて、そこにいるサブモジュールを、「親が認識している子の年齢」、つまり10歳にアップデートしましょう。

//cmd{
メインプロジェクトが認識しているサブモジュールの状態にアップデートする
$ git submodule update
Submodule path 'prh-rules': checked out '782af14a4dae78d62b591f7dab818826f721ca70'　←10歳のサブモジュールを連れてきた
//}

@<code>{git pull}したことで、メインリポジトリが認識しているサブモジュールのコミットが変わったんだから、そこはちゃんと付いてこいよ！と思いますが、そいうものなのです。筆者は@<code>{git pull && git submodule update}を叩いたら楽なのかな、と思ったりします。

== 正しい差分の無くし方

@<code>{cd}コマンドでサブモジュールに移動して、そこで@<code>{git pull}してはいけないのです。親の認識にかかわらず、子が最新版になってしまいます。最新版が10歳で、親の認識も10歳であれば問題ありませんが、いずれにしてもこの方法はお勧めしません。

メインプロジェクトが認識している、サブモジュールの状態にアップデートしたければ、@<code>{git submodule update}を使いましょう。

筆者は@<code>{git pull && git submodule update}を叩いたら楽なのかな、と思ったりします。
