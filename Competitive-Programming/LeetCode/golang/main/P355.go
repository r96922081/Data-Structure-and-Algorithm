package main

import "fmt"

func main() {
    fmt.Println("P355")
}

type post struct {
	id        int
	timestamp int
}

type Twitter struct {
	timestamp int
	tweets    map[int][]post
	followed  map[int]map[int]bool
}

/** Initialize your data structure here. */
func Constructor() Twitter {
	twitter := Twitter{}
	twitter.tweets = make(map[int][]post)
	twitter.followed = make(map[int]map[int]bool)
	return twitter
}

func (this *Twitter) AddUserOnDemand(userId int) {
	_, ok := this.tweets[userId]
	if ok {
		return
	}
	this.tweets[userId] = make([]post, 0)
	this.followed[userId] = make(map[int]bool)
}

/** Compose a new tweet. */
func (this *Twitter) PostTweet(userId int, tweetId int) {
	this.AddUserOnDemand(userId)

	v, _ := this.tweets[userId]
	this.tweets[userId] = append(v, post{tweetId, this.timestamp})
	this.timestamp++
}

/** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
func (this *Twitter) GetNewsFeed(userId int) []int {
	this.AddUserOnDemand(userId)

	interestedUserTweets := make([][]post, 0)
	interestedUserTweets = append(interestedUserTweets, this.tweets[userId])

	for key := range this.followed[userId] {
		interestedUserTweets = append(interestedUserTweets, this.tweets[key])
	}

	ret := make([]int, 0)
	for dummy := 0; dummy < 10; dummy++ {
		maxTimeStamp := -1
		selection := -1
		selectedPost := post{}

		for i := range interestedUserTweets {
			interestedUserTweets2 := interestedUserTweets[i]
			if len(interestedUserTweets2) == 0 {
				continue
			}
			post := interestedUserTweets2[len(interestedUserTweets2)-1]
			if post.timestamp > maxTimeStamp {
				maxTimeStamp = post.timestamp
				selection = i
				selectedPost = post
			}
		}

		if selection == -1 {
			break
		}

		ret = append(ret, selectedPost.id)
		interestedUserTweets[selection] = interestedUserTweets[selection][:len(interestedUserTweets[selection])-1]
	}

	return ret
}

/** Follower follows a followee. If the operation is invalid, it should be a no-op. */
func (this *Twitter) Follow(followerId int, followeeId int) {
	this.AddUserOnDemand(followerId)
	this.AddUserOnDemand(followeeId)
	if followerId == followeeId {
		return
	}

	m, _ := this.followed[followerId]
	_, ok := m[followeeId]
	if !ok {
		m[followeeId] = true
	}
	this.followed[followerId] = m
}

/** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
func (this *Twitter) Unfollow(followerId int, followeeId int) {
	this.AddUserOnDemand(followerId)
	this.AddUserOnDemand(followeeId)

	m, _ := this.followed[followerId]
	_, ok := m[followeeId]
	if ok {
		delete(m, followeeId)
	}
	this.followed[followerId] = m
}
