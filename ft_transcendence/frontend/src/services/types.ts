import type { User } from '../types/auth';

export type ErrorPayload = { error?: unknown };
export type BasicResponse = { success?: boolean; error?: string };
export type UserResponse = { success?: boolean; user?: User; error?: string };
export type ProfileUpdatePayload = {
  username?: string;
  email?: string;
  avatar_url?: string;
  language?: 'en' | 'fr' | 'ar';
};

export type Friend = {
  id: number;
  username: string;
  avatarUrl: string | null;
  isActive: boolean;
};

export type FriendRequest = {
  id: number;
  username: string;
  avatarUrl: string | null;
};

export type FriendsListResponse = { friends?: Friend[]; error?: string };
export type FriendRequestsResponse = { received?: FriendRequest[]; sent?: FriendRequest[]; error?: string };

export type UserProfileStats = {
  gamesPlayed:     number;
  gamesWon:        number;
  gamesLost:       number;
  blackjacksWon:   number;
  blackjackLosses: number;
  rouletteWins:    number;
  rouletteLosses:  number;
};

export type UserProfile = {
  id:          number;
  username:    string;
  avatarUrl:   string | null;
  bio:         string | null;
  isOnline:    boolean;
  createdAt:   string | null;
  coins:       number;
  isFriend:    boolean;
  hasPending:  boolean;
  stats:       UserProfileStats | null;
};

export type UserProfileResponse = { profile?: UserProfile; error?: string };
