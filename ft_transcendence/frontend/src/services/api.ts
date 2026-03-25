import type { User, RegisterData, LoginData, AuthResponse }                                                       from '../types/auth';
import type { ErrorPayload, BasicResponse, UserResponse, ProfileUpdatePayload, FriendsListResponse, FriendRequestsResponse, UserProfileResponse } from './types';
import type { BlackjackResponse } from '../types/game';

const BASE_URL   = '';
const API_URL    = `${BASE_URL}/api/auth`;
const SOCIAL_URL = `${BASE_URL}/api/social`;
const GAMES_URL  = `${BASE_URL}/api/games`;

const stringifyError = (payload: ErrorPayload | null | undefined): string =>
{
  const raw = payload?.error;

  if (!raw)                    return 'Request failed';
  if (typeof raw === 'string') return raw;
  if (typeof raw !== 'object') return 'Request failed';

  try
  {
    const messages: string[] = [];
    const stack: unknown[]   = [raw];

    while (stack.length)
    {
      const current = stack.pop();
      if (!current || typeof current !== 'object')
        continue;

      const obj = current as Record<string, unknown>;

      if (typeof obj.message === 'string')
        messages.push(obj.message);

      if (Array.isArray(obj.issues))
      {
        obj.issues.forEach((issue) =>
        {
          if (issue && typeof issue === 'object' && typeof (issue as Record<string, unknown>).message === 'string')
            messages.push((issue as Record<string, unknown>).message as string);
        });
      }

      Object.values(obj).forEach((value) => stack.push(value));
    }

    if (messages.length > 0)
      return messages[0]!;
  }
  catch { return 'Request failed'; }

  return 'Request failed';
};

async function apiCall<T>(
  path:   string,
  method: 'GET' | 'POST' | 'PUT' | 'DELETE',
  data?:  unknown
): Promise<T & { error?: string }>
{
  try
  {
    const options: RequestInit = {
      method,
      credentials: 'include',
    };

    if (data !== undefined)
    {
      options.headers = { 'Content-Type': 'application/json' };
      options.body    = JSON.stringify(data);
    }

    const response = await fetch(`${API_URL}/${path}`, options);
    const result   = await response.json();

    if (!response.ok)
      return { error: stringifyError(result) } as T & { error: string };
    return result;
  }
  catch { return { error: 'Network error' } as T & { error: string }; }
}

async function socialCall<T>(
  path:   string,
  method: 'GET' | 'POST' | 'PUT' | 'DELETE',
  data?:  unknown
): Promise<T & { error?: string }>
{
  try
  {
    const options: RequestInit = {
      method,
      credentials: 'include',
    };

    if (data !== undefined)
    {
      options.headers = { 'Content-Type': 'application/json' };
      options.body    = JSON.stringify(data);
    }

    const response = await fetch(`${SOCIAL_URL}/${path}`, options);
    const result   = await response.json();

    if (!response.ok)
      return { error: stringifyError(result) } as T & { error: string };
    return result;
  }
  catch { return { error: 'Network error' } as T & { error: string }; }
}

async function gameCall<T>(
  path:   string,
  method: 'GET' | 'POST' | 'PUT' | 'DELETE',
  data?:  unknown
): Promise<T & { error?: string }>
{
  try
  {
    const options: RequestInit = {
      method,
      credentials: 'include',
    };

    if (data !== undefined)
    {
      options.headers = { 'Content-Type': 'application/json' };
      options.body    = JSON.stringify(data);
    }

    const response = await fetch(`${GAMES_URL}/${path}`, options);
    const result   = await response.json();

    if (!response.ok)
      return { error: stringifyError(result) } as T & { error: string };
    return result;
  }
  catch { return { error: 'Network error' } as T & { error: string }; }
}

export const api = {
  register:           (data: RegisterData)          => apiCall<AuthResponse>('register',      'POST', data),
  login:              (data: LoginData)              => apiCall<AuthResponse>('login',         'POST', data),
  me:                 ()                             => apiCall<{ user: User | null }>('me',   'GET'),
  resendVerification: ()                             => apiCall<BasicResponse>('verify/resend','POST'),
  updateProfile:      (payload: ProfileUpdatePayload)=> apiCall<UserResponse>('profile',       'PUT',  payload),
  logout:             ()                             => apiCall<BasicResponse>('logout',       'POST'),
  enable2FA:          ()                             => apiCall<{ secret?: string; uri?: string }>('2fa/enable',  'POST'),
  verify2FA:          (code: string)                 => apiCall<BasicResponse>('2fa/verify',   'POST', { code }),
  disable2FA:         ()                             => apiCall<BasicResponse>('2fa/disable',  'POST'),

  getFriends:         ()                             => socialCall<FriendsListResponse>('friends',          'GET'),
  getFriendRequests:  ()                             => socialCall<FriendRequestsResponse>('friends/requests', 'GET'),
  sendFriendRequest:  (username: string)             => socialCall<BasicResponse>('friends/request',   'POST', { username }),
  acceptFriendRequest:(senderId: number)             => socialCall<BasicResponse>('friends/accept',    'POST', { senderId }),
  refuseFriendRequest:(senderId: number)             => socialCall<BasicResponse>('friends/refuse',    'POST', { senderId }),
  cancelFriendRequest:(receiverId: number)           => socialCall<BasicResponse>('friends/cancel',    'POST', { receiverId }),
  removeFriend:       (friendId: number)             => socialCall<BasicResponse>('friends',           'DELETE', { friendId }),
  getUserProfile:     (userId: number)               => socialCall<UserProfileResponse>(`profile/${userId}`, 'GET'),

  blackjackNew:       (bet: number)                  => gameCall<BlackjackResponse>('blackjack/new',    'POST', { bet }),
  blackjackHit:       ()                             => gameCall<BlackjackResponse>('blackjack/hit',    'POST'),
  blackjackStand:     ()                             => gameCall<BlackjackResponse>('blackjack/stand',  'POST'),
  blackjackDouble:    ()                             => gameCall<BlackjackResponse>('blackjack/double', 'POST'),
  blackjackGet:       ()                             => gameCall<BlackjackResponse>('blackjack',        'GET'),

  createRoom:         (withBot?: boolean)            => gameCall<any>('rooms/create', 'POST', { withBot }),
  joinRoom:           (roomId?: string, code?: string) => gameCall<any>('rooms/join', 'POST', { roomId, code }),
  listRooms:          ()                             => gameCall<any>('rooms', 'GET'),
  getRoom:            (roomId: string)               => gameCall<any>(`rooms/get?roomId=${roomId}`, 'GET'),
  startRoomGame:      (roomId: string, bet: number) => gameCall<any>('rooms/start', 'POST', { roomId, bet }),
  getRoomGameState:   (roomId: string)               => gameCall<any>(`rooms/game-state?roomId=${roomId}`, 'GET'),
};
