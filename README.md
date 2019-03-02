# Title Case Converter

A command line script that takes a list of words and converts their case using
1 of 6 industry standard style guides.

*It's a self contained Python 2.x and 3.x compatible script that only requires
having `curl` installed.*

## Example

#### Positional Arguments

```
nick:~$ tcc hello world, this is a test
Hello World, This Is a Test
```

The basic idea is you supply a list of words as input and it produces the
converted title as output.  You can choose to either input each word as a
separate argument (as seen above) or pass in a quoted string of words.

The quoted string of words is useful if you want to use `&` in your title and
don't want to worry about escaping it. An example of that would be: `tcc "ren
& stimpy"`, which would produce `Ren & Stimpy` as output.

#### Piping Output from Another Program

If you want to pipe the output of another program as input to `tcc`, that works
too.

`echo hello world, this is a test | tcc` produces the same output as
`tcc hello world, this is a test`.

## Style Guides

You can pass in an optional `--style X` argument where `X` is one of the
letters below.

```
A: Associated Press Stylebook
P: Publication Manual of the American Psychological Association
C: Chicago Manual of Style (default)
M: MLA Handbook
N: The New York Times Manual of Style and Usage
W: Wikipedia Manual of Style
```

`tcc --style N hello world` would use the New York Times Manual of Style
instead of the Chicago Manual of Style (default).

## Installation

All you have to do is download the `tcc` script, make sure it's executable
and place it somewhere on your system path.

#### 1 liner to get `tcc` downloaded to `/usr/local/bin`:

```sh
sudo curl \
  -L https://raw.githubusercontent.com/nickjj/title-case-converter/master/tcc \
  -o /usr/local/bin/tcc && sudo chmod +x /usr/local/bin/tcc
```

You can confirm it works by running `tcc --help`.

## How It Works / Credits 

A lot of libraries will capitalize every word but then have a black list of
words to skip such as "a" or "or", but this strategy isn't accurate at all.
Instead, this script calls out
[https://titlecaseconverter.com/](https://titlecaseconverter.com/) which does
all of the heavy lifting.

The Title Case Converter website is not managed by me. All my script does is
pass a list of words to that site, allows you to pick which strategy to use and
curls everything over. You can check out the source code to see how it works.

It's basically a limited terminal UI to the site. I say "limited" because the
website provides additional information about how and why each word was
capitalized. It's an excellent resource for learning these styles in detail.

The author of the site gave me permission to create and open source this script.
He has put in hundreds of hours of effort into creating this service. If you
want to support his work, he has a
[donation link](https://titlecaseconverter.com/) on the bottom of the page.

The owner of the Title Case Converter site generates income from
ads on his site, and using this CLI tool means you won't be viewing those ads.
Although truthfully, you probably have an ad blocker running so it doesn't
matter, but in either case if you find his service useful and it saves you time
then donate something to him because without this service, this script won't
exist.

### What's with Setting `tcc` as the User Agent?

I don't receive any kick backs on donations or anything like that and the
author didn't even ask me to set a custom user agent, but I thought it would
be a good idea so that he can see which titles are being converted by this tool.

If you don't want this behavior, you can edit the script to remove `-A "tcc"`
from the curl command but now the user agent is going to come up as Curl
instead which still shows you're using the service outside of his site. You
could also choose to set it to some well known browser's UA too, but you're not
gaining much by doing this. Your titles are still sent to his server.

### Why Not Just Use the Site Directly?

You absolute can and in some cases such as converting multiple titles at once,
it's worth using the site directly.

But having a CLI script that produces a converted title as output allows you to
integrate it with your favorite code editor.

For example, you can set up a custom key binding with your code editor which
takes your selected text, passes that text in as input to this `tcc` script
and then replaces the selected text with `tcc`'s output.
