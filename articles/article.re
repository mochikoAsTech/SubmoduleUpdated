
= ああサブモジュール、君のこと（挙動）が分からない

== Gitとは

本書はGitのサブモジュールの挙動が分からずに苦しむ人のための本なので、Gitそのものについては解説しません。
「Gitについて何も知らないので1から学びたい」という方には、湊川あいさんの書籍がお勧めです。

 * わかばちゃんと学ぶ Git使い方入門
 ** @<href>{https://www.amazon.co.jp/dp/4863542178}

「お金をかけずにまずは無料で学びたい」という場合は、先ほどの本の元となったウェブ連載を読みましょう。

 * マンガでわかるGit 第1話「Gitってなあに？」
 ** @<href>{https://next.rikunabi.com/journal/20160526_t12_iq/}

なんと最近はGitをコマンドで使う方法を学ぶ「コマンド編」も連載されているそうです。

 * マンガでわかるGit ～コマンド編～ 第1話「リポジトリを作ってコミットしてみよう」
 ** @<href>{https://www.r-staffing.co.jp/engineer/entry/20190621_1}

Gitは付け焼き刃の操作だけを学ぶよりも、どういう仕組みで、どんな理屈で動いているのかをしっかり学んだ方が、結果としては理解の速度が上がります。
わかばちゃんと一緒にたくさん転んで、Gitを楽しく学んでみてください。

== Gitのサブモジュールとは

プロジェクトAとプロジェクトBの両方で同じライブラリを使いたい！
そのライブラリをメンテナンスするのはプロジェクトCのみなさんだとします。

このときプロジェクトAのリポジトリにも、プロジェクトBのリポジトリにもライブラリのソースコードを直接置いてしまう（プロジェクトのツリーに取り込んでしまうと）と、プロジェクトCのメンバーがライブラリをメンテナンスしたいときに、両方のリポジトリでそれぞれ更新しなければなりません。

Gitのサブモジュールを使うと、プロジェクトCのリポジトリを、別のリポジトリのサブディレクトリとして扱えるようになります。プロジェクトAやプロジェクトBを親（メイン）としたとき、子（サブ）にあたるプロジェクトCのコミットは、親のコミットとは別で管理できます。

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

サブモジュールを追加するとき、先ほどのように特にディレクトリ名を指定しないと、サブモジュールのリポジトリ名（@<code>{SubmoduleUpdated}）がそのままディレクトリ名となります。（@<img>{SubmoduleUpdated_1}）

//image[SubmoduleUpdated_1][SubmoduleUpdatedがサブモジュールとして追加された][scale=0.8]{
//}

ディレクトリ名を変えたいときは、次のように末尾でディレクトリ名を指定してやれば、たとえばディレクトリ名を「sub」にした状態でサブモジュールを追加できます。

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

サブモジュールを追加すると、このように親のリポジトリに@<code>{.gitmodules}というファイルが生まれます。これはテキスト形式の設定ファイルで、テキストエディタで開くとこんなふうにサブモジュールのディレクトリパスと、リモートのURLが書かれています。サブモジュールを複数追加すると、このファイルにその分いくつも追記されていきます。

//cmd{
[submodule "SubmoduleUpdated"]
	path = SubmoduleUpdated
	url = https://github.com/mochikoAsTech/SubmoduleUpdated
//}

他の人がメインリポジトリをクローンすると、このファイルに書かれた内容を元に、サブモジュールの取得元を把握することになります。

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

実際はSubmoduleUpdatedはディレクトリであり、その中にはたくさんの原稿ファイルがあります。ですがメインのリポジトリからは、サブモジュールの中身を1つ1つ追跡するようなことはおこないません。代わりにこのサブディレクトリを、親から見た「子の年齢」のような@<code>{+Subproject commit 6f47087f1c9079ea6c677702da23ca040d0a13ed}という1つのコミットとして記録していることが分かります。

== サブモジュールを含むリポジトリをクローンしてこよう

サブモジュールを含むメインのリポジトリをクローンすると、最初は「サブモジュールが入っているはずのディレクトリ」は取得できるのですが、その中身は空っぽです。

//cmd{
ローカルの設定ファイルを初期化する
$ git submodule init

親から見た年齢（コミット）のサブモジュールを連れてくる
$ git submodule update
//}

== 最初からサブモジュールの中身も含めて全部連れてきたかった

最初からサブモジュールの中身も含めて全部まるっと持ってきたい場合は、@<code>{--recursive}オプションを付けてクローンしてきます。

//cmd{
サブモジュールも含めて全部まるっとクローンしてくる
$ git clone --recursive https://github.com/mochikoAsTech/SubmoduleUpdated
//}

== 親子の関係

Gitのメインリポジトリを親、サブモジュールを子だとします。

サブモジュールのリポジトリではコミットが「A→B→C」で進んでいて、けれど親のリポジトリではまだBを参照しているとします。
この場合、親のリポジトリで@<code>{git submodule update}したら、サブモジュールはBを引っ張ってきます。

@<code>{git submodule update}とは、「子のサブモジュールを最新にしておくれ」ではなく、「"親が指定している子のコミット"に更新しておくれ」なのです。

== git pullしただけなのに差分が出た
== git checkoutしただけなのに差分が出た
== サブモジュールでgit pullしただけなのに差分が出た
== 正しい差分の無くし方
