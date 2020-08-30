= はじめに

//flushright{

2020年9月
mochikoAsTech

//}

本書を手に取ってくださったあなた、こんにちは！あるいは、はじめまして。
「何もしてないのに突然Submoduleの差分が出て泣きそうになったら読む本」の筆者、mochikoAsTechです。

== 想定する読者層

本書は、こんな人に向けて書かれています。

 * 仕事で使っているリポジトリにSubmoduleがいる
 * なぜかgit pullしただけなのにSubmoduleの差分が出て納得いかない
 * git checkoutして別ブランチに移動しただけなのにSubmoduleの差分がでて納得いかない
 * ちゃんとgit pullしたのにSubmoduleが更新されなくて困っている
 * Submoduleのフォルダまで移動してgit pullしただけなのに差分が出てわけが分からない
 
== マッチしない読者層

本書は、こんな人が読むと恐らく「not for meだった…（私向けじゃなかった）」となります。

 * Gitについて何も知らないので1から学びたい
 * プロジェクトでSubmoduleを導入すべきか迷っていて判断材料が欲しい
 * いまからリポジトリにSubmoduleを入れようとしているので方法が知りたい

== 本書のゴール

本書を読み終わると、あなたはこのような状態になっています。

 * Submoduleの仕組みが分かっている
 * 意図せぬSubmoduleの差分が出た時に対処できる
 * 読む前よりSubmoduleがちょっと好きになっている

== 免責事項

本書に記載されている内容は筆者の所属する組織の公式見解ではありません。

また本書はできるだけ正確を期すように努めましたが、筆者が内容を保証するものではありません。よって本書の記載内容に基づいて読者が行なった行為、及び読者が被った損害について筆者は何ら責任を負うものではありません。

不正確あるいは誤認と思われる箇所がありましたら、必要に応じて適宜改訂を行いますのでGitHubのIssueやPull requestで筆者までお知らせいただけますと幸いです。

@<href>{https://github.com/mochikoAsTech/SubmoduleUpdated}
